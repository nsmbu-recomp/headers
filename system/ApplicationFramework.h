#pragma once

#include <cstddef>

#include <framework/cafe/seadGameFrameworkCafe.h>

#include <cafe/procui.h>

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
    void procDraw_() override;

    void calc_();
    void procCalc_() override;

    void swapBuffer_() override;

    void waitStartDisplayLoop_() override;

protected:
    sead::MultiProcessMeterBar<1>   mLayerMgrCalcMeter; // sead::MultiProcessMeterBar<???>
    sead::MultiProcessMeterBar<1>   _380;               // sead::MultiProcessMeterBar<???>
    bool                            mFirstSwapDone;
    s32                             mCalcPassCount;     // +0x38C; see docs/frame-loop.md
    s32                             mSkippedCalcCount;  // +0x390
    ProcUIStatus                    mProcUIStatus;
};
static_assert(sizeof(ApplicationFramework) == 0x398);
static_assert(offsetof(ApplicationFramework, mCalcPassCount) == 0x38C);
static_assert(offsetof(ApplicationFramework, mSkippedCalcCount) == 0x390);
