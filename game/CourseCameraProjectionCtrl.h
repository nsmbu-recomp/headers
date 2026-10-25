#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>

class CourseCameraUpdater;

using CourseCameraUpdaterFn = void (*)(CourseCameraUpdater*);

class CourseCameraProjectionCtrl
{
public:
    u8                      _00[0x6C];
    CourseCameraUpdaterFn   fn_6C_;
    u8                      _70[0xD4 - 0x70];
    CourseCameraUpdaterFn   fn_D4_;
    u8                      _D8[0xDC - 0xD8];
    CourseCameraUpdaterFn   fn_DC_;
    u8                      _E0[0xE4 - 0xE0];
    CourseCameraUpdaterFn   fn_E4_;
    u8                      _E8[0xEC - 0xE8];
    CourseCameraUpdaterFn   fn_EC_;
};

// Address: 0x02A05C68
void CourseCameraApplyProjection(CourseCameraUpdater* updater, sead::Matrix44f* matrix, void* copy_dest, u32 mode);
