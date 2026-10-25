#pragma once

#include <state/IState.h>

class CourseCameraProjectionCtrl;

class CourseCameraUpdater : public IState
{
public:
    // Address: 0x02A031A0
    void execute() override;

    const StateID* getStateID() const override;

private:
    u8                          _04[0x14];
    void*                       mpSub;
    u8                          _1c[8];
    CourseCameraProjectionCtrl* mpProjCtrl;
    s32                         mStep;
    u8                          _2c[0x6c - 0x2c];
    u32                         mFlags;
    u32                         mField70;
    u32                         mField74;
    u32                         mTimePart0;
    u32                         mTimePart1;
    u8                          _80[0x370 - 0x80];
    void*                       mpKeyframes;
    u8                          _374[0x3E4 - 0x374];
};
static_assert(sizeof(CourseCameraUpdater) == 0x3E4);
