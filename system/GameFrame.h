#pragma once

#include <cstddef>

#include <cafe/procui.h>
#include <framework/cafe/seadGameFrameworkCafe.h>

namespace sead {
class TaskBase;
}

class GameFrame : public sead::GameFrameworkCafe
{
public:
    void procDraw_();
    void procCalc_();
    void calc_();

private:
    void bindFrameBuffer_(sead::FrameBuffer* buffer);
    void invokeDrawAt0xAC_();
    sead::TaskBase* runRootTaskProcDraw_(sead::TaskBase* root);
    void callRootMethodTree_(sead::TaskBase* root, u32 byte_offset);

    sead::MultiProcessMeterBar<1>   mLayerMgrCalcMeter;
    sead::MultiProcessMeterBar<1>   _380;
    bool                            mFirstSwapDone;
    s32                             mCalcPassCount;
    s32                             mSkippedCalcCount;
    ProcUIStatus                    mProcUIStatus;
};
static_assert(sizeof(GameFrame) == 0x398);
static_assert(offsetof(GameFrame, mCalcPassCount) == 0x38C);
static_assert(offsetof(GameFrame, mSkippedCalcCount) == 0x390);
