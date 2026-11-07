#pragma once

#include <cstddef>

#include <framework/cafe/seadGameFrameworkCafe.h>

#include <cafe/procui.h>

// USA v1.3.0 frame loop. NSMBU logic is one 60 Hz step per TV vsync.
// It does not scale gameplay by wall-clock delta.
// Same RPX class as GameFrame. Size is 0x398.
// The ctor is the 0x029C4DC0 family. It sets mCalcPassCount to 1 and mSkippedCalcCount to 0.
//
// sead::GameFrameworkCafe::procFrame_ is 0x02A031A0.
// runImpl_ is 0x02A02EB4. mainLoop_ is 0x02A02F48.
// That procFrame_ PC is not CourseCameraUpdater::execute.
// Overridable steps are a static dispatch table at 0x10185280, held at this+0x24, not a vtable.
// Slots: +0xD4 procDraw_, +0xDC procCalc_, +0x6C procReset_, +0xE4 waitForNextFrame_, +0xEC swapBuffer_.
// Base procDraw_ is 0x02A0358C. Base swapBuffer_ is 0x02A03798. waitForNextFrame_ is 0x02A03748.
//
// Each procFrame_:
// 1. sead::Graphics::lockDrawContext (0x02A07A54).
// 2. sead::TaskMgr::afterCalc (0x02A0183C, a b onto 0x02A01730) for the previous frame.
// 3. procDraw_.
// 4. procCalc_.
// 5. procReset_. The name is inferred. The +0x6C body drains a callback list and clears one byte.
// 6. swapBuffer_. GX2SwapScanBuffers when the display state is Show, then GX2DrawDone.
// 7. gpuMesureEnd_ (0x02A02F74).
// 8. unlockDrawContext (0x02A07AF8).
// 9. Store mFrameSpan from mLastFrameBegin.diffToNow(), then stamp mLastFrameBegin again.
// 10. waitForNextFrame_.
//
// lockDrawContext and unlockDrawContext read the Cafe thread-specific slot id at *(0x101E80A0)+0x20, then OSGetThreadSpecific.
// lockDrawContext compares that against +0x10, bumps the +0x14 refcount, and otherwise locks the CriticalSection at +0x18 before the lockDrawContextImpl virtual (vtable+0x8C).
// unlockDrawContext decrements +0x14 and, at zero, clears +0x10, runs unlockDrawContextImpl (vtable+0x90), and unlocks +0x18.
// Prepare Thread takes this lock while it builds a course. Boot, save, and level loads take it while the screen is black.
// A present that spends the whole slot inside procFrame_ leaves that thread waiting on the lock.
// afterCalc calls MethodTreeNode::call (0x029FF618) on TaskMgr+0x14C, then walks the destroyable list at vtable+0x30.
// gpuMesureEnd_ runs DCInvalidateRange(mGpuCounters, 0x20). mDrawOrder at +0xC0 selects the TV and DRC GX2GPUTimeToCPUTime pairs.
//
// mFrameSpan is +0x70 (a 64-bit stamp). mLastFrameBegin is +0x78.
// mFrameSpan is written at 0x02A03260. The new stamp is at 0x02A03278.
// Neither the sead framework nor the app overrides load +0x70 or +0x74. calcFps has no reader in USA v1.3.0.
//
// waitForNextFrame_ runs only when CreateArg::wait_vblank is non-zero (default 1).
// It loops GX2WaitForVsync and GX2GetSwapStatus until flipCount >= swapCount.
// initializeGraphicsSystem also calls GX2SetSwapInterval(wait_vblank).
// One guest frame is one TV vsync by default.
//
// The word at +0x6C is mFlag. Bit 0 is a half-frame mode in sead.
// With bit 0 set, alternate procFrame_ calls skip swapBuffer_ and gpuMesureEnd_. The xori at 0x02A03298 toggles bit 1.
// Base procDraw_ and base swapBuffer_ test that pair and skip the screen draws.
// The app procDraw_ override does not test it.
// The ctor zeroes +0x6C. No writer of bit 0 was found, so NSMBU leaves the flag clear in normal play.
//
// this+0x1C is sead::DualScreenMethodTreeMgr (ctor 0x029FC8BC, size 0x3E4, vtable 0x1018FEB8).
// It is MethodTreeMgr (0x40: vtable + CriticalSection), then eleven MethodTreeNode (0x54 each), then the two Screen fields.
// Node names are rodata strings at 0x1018FDE0-0x1018FEA4:
// +0x040 RootCalc, +0x094 SysCalc, +0x0E8 AppCalc,
// +0x13C TopRootDraw, +0x190 TopSysDraw, +0x1E4 TopAppDraw, +0x238 TopAppDrawFinal,
// +0x28C BtmRootDraw, +0x2E0 BtmSysDraw, +0x334 BtmAppDraw, +0x388 BtmAppDrawFinal.
// 0x029FF490 is appendChild.
// RootCalc holds SysCalc and AppCalc.
// TopRootDraw holds TopAppDraw, TopAppDrawFinal, and TopSysDraw.
// BtmRootDraw holds BtmAppDraw, BtmAppDrawFinal, and BtmSysDraw.
// 0x029FF618 is MethodTreeNode::call. It locks node+0x3C, runs 0x029FF588, and unlocks.
// 0x029FF588 skips when mPauseFlag at +0x44 bit 0 is set. Otherwise it invokes the +0x2C delegate and recurses.
// 0x029FD93C is calc and calls RootCalc at +0x40.
class ApplicationFramework : public sead::GameFrameworkCafe
{
    SEAD_RTTI_OVERRIDE(ApplicationFramework, sead::GameFrameworkCafe)

public:
    static u32 toSeconds(u32 hours);
    static u32 toHours(u32 seconds);
    static u32 getTimeBeforeAPD();  // In hours, APD = Auto Power Down
    static void setDimEnable(bool enable);
    static bool isDimEnable();

public:
    ApplicationFramework(const CreateArg& arg);

    void run(sead::Heap* heap, const sead::TaskBase::CreateArg& root_create_arg, const RunArg& run_arg) override;
    void createProcessMeter(sead::TaskBase* root_task) override;

protected:
    // Address: 0x029C4FE4
    // Draws the TV method tree, then the DRC method tree.
    // drawTop is 0x029FD944 and calls the node at +0x13C. drawBtm is 0x029FD94C and calls the node at +0x28C.
    // drawTop finishes before drawBtm starts. The two trees write separate screen targets.
    // The TV picture does not sample this frame's GamePad targets.
    // After each of those two calls the override calls dispatch slot +0xAC (0x029C5734). That body is `li r3, 0; blr`.
    // The base table 0x101906D4 puts the pure-virtual panic (0x02AFA5E8) in that slot. The override only silences it.
    // GX2SetContextState (0x029C50E4, on *(0x101F8000)+0x134) and GX2Flush (0x029C50E8) run after both draws.
    // Base procDraw_ (0x02A0358C) calls 0x02A032C8 and 0x02A03394 instead.
    // procDraw_ runs before procCalc_ in the same present.
    // On the world map the present after a hold calc is the stable one, because that calc leaves the light maps alone.
    // The present whose calc is the logic step rebuilds those maps after the draw has already been recorded.
    // Course play still draws every present. NSMBU's native rate is 60 steps per second.
    void procDraw_() override;

    // Address: 0x029C5104
    // Waits on GX2DrawDone, copies the TV and DRC framebuffers to the display buffers, flushes, and runs LayerMgr::calcParallelExec.
    // A hold or in-between present calls only this path, so the task tree does not advance.
    // The recorded display list is what that present shows. calcGPU does not run again on a hold.
    void calc_();

    // Address: 0x029C52CC
    // mCalcPassCount is +0x38C. mSkippedCalcCount is +0x390.
    // When mCalcPassCount > 0: clear the render mgr, run GameFrameworkCafe::procCalc_ once,
    // call the app calc method-tree root (getRootMethodTreeNode(1)) an extra mCalcPassCount - 1 times,
    // then LayerMgr::calcDL and calc_.
    // When mCalcPassCount <= 0: count skips until skipped + 1 >= -mCalcPassCount, then run one full calc and reset the skip counter.
    // The default is 1, one calc per frame. No in-tree writer of another value was found.
    // calcDL and calc_ are skipped when LayerMgr::sInstance (*(0x101D2BE4)) is null.
    // The full logic path runs clearRenderMgr, the task tree (including LightMapMgr::calc at 0x024E5008), LayerMgr::calcDL (0x024E0F84), then calc_.
    // mCalcPassCount above 1 repeats the app calc node, so both steps' draw objects land in one picture.
    // A second clear in the same call, without the GX2DrawDone wait in calc_, frees a list the render thread is still reading.
    // A second LayerMgr::calcDL crashes in the layer builder (0x02509488, null+4).
    void procCalc_() override;

    // Address: 0x029C53F8
    // Adds the first-swap TV and DRC enable, and ProcUI / HBM handling, on top of GameFrameworkCafe::swapBuffer_ (0x02A03798).
    // The first-swap flag is the byte at +0x388. The ProcUI result is kept at +0x394.
    // A 3 from ProcUIProcessMessages runs ProcUIShutdown and exits through __PPCExit.
    void swapBuffer_() override;

    void waitStartDisplayLoop_() override;

protected:
    sead::MultiProcessMeterBar<1>   mLayerMgrCalcMeter; // sead::MultiProcessMeterBar<???>
    sead::MultiProcessMeterBar<1>   _380;               // sead::MultiProcessMeterBar<???>
    bool                            mFirstSwapDone;
    s32                             mCalcPassCount;     // +0x38C; 1 is one calc per frame. See procCalc_.
    s32                             mSkippedCalcCount;  // +0x390
    ProcUIStatus                    mProcUIStatus;
};
static_assert(sizeof(ApplicationFramework) == 0x398);
static_assert(offsetof(ApplicationFramework, mCalcPassCount) == 0x38C);
static_assert(offsetof(ApplicationFramework, mSkippedCalcCount) == 0x390);
