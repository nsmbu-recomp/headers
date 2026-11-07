#pragma once

#include <heap/seadDisposer.h>
#include <filedevice/cafe/seadCafeFSAFileDeviceCafe.h>

// USA 1.3.0 setup is 0x029D4818. It calls 0x029D4548.
// 0x029D4548 uses nn_aoc in this order:
// AOC_Initialize, AOC_CalculateWorkBufferSize(1), AOC_ListTitle(&count, title, 1, work, workSize).
// It stops when count is not 1, then calls AOC_OpenTitle(path, title, work, workSize).
// The title record is 0x61 bytes. The path result is a C string. The game appends "/0010".
// That string is the root of the sead device named "rdash".
// mIsDrivePresent (+0x10) stores the mount result. A result of 0 leaves the eShop prompt on the title.
// mIsNSLU is +0x11.
// The story-map notice is 0x02632418 (Europe 1.3.0: 0x026324BC). Base discs do not have that function.
// It requests SaveData_Rdash_info_00, index 0 in the common-window table at 0x102145B4,
// stores the index at window-task +0x1A34, and sets byte +0x1A3C. 0x025D065C then opens the window.
// 0x02632458 writes 1 to SaveData::header.rdash_state after the player closes it.
class RDashMgr
{
    SEAD_SINGLETON_DISPOSER(RDashMgr)

public:
    RDashMgr();

    bool isNSLU() const { return mIsNSLU; }

private:
    bool                        mIsDrivePresent;
    bool                        mIsNSLU;
    sead::CafeFSAFileDevice*    mpFileDevice;
};
static_assert(sizeof(RDashMgr) == 0x18);
