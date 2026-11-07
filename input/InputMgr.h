#pragma once

#include <heap/seadDisposer.h>
#include <random/seadRandom.h>

class InputMgr;

// Address: 0x0250C3EC
// Reads the active save slot record at InputMgr+0x55C (0x204 bytes per file in SaveMgr)
// and writes FieldGameData, FieldGameMode, MainGame, and a few globals.
// The only callers are InputMgr::applySaveEntry_ (bl at 0x0250CFA0 and 0x0250CFC0).
// Course setup reaches that from CourseTask::setupCourse after InputMgr::createInstance.
//
// Per player, four times, stride 0x10, base +0x3C:
// +0x00 u8 is_entry, +0x01 u8 life_cnt (clamped 99 to 5), +0x02 u8 character,
// +0x03 u8 character_color through 0x0250C3C8, +0x04 u8 player_mode, +0x05 u8 has_star,
// +0x06 u8 bit0 to mii_cap_visible and mii_slot with MainGame+0x2C bit4 and SubjectMgr+0x1E7E,
// +0x08 u32 coin_cnt. +0x07 is not read.
// Mii slot assignment uses cap and normal counters when the color is Mii.
//
// Course and mode bytes:
// +0x7C..+0x7E banner picture-pane digits at FieldGameData+0x13D..+0x13F (clamped, -1 blank).
// +0x43 setCheckPoint index. The world, course, and file arguments are live CourseInfo::mCourseNow (+0x10/+0x11/+0x12), not the save map coordinates.
// Banner digits copied to the checkpoint come from the stack copy of +0x13D..+0x13F.
// +0x44 checkpoint _0c (clamp < 4). +0x45 checkpoint _08 (0 or 1). +0x46 checkpoint next_goto_no.
// +0x47 MainGame+0x21DFA/B (bit0/bit1). If bit0, MainGame+0x1E0 = bit1.
// +0x48 FieldGameMode::setMode. +0x49 FieldGameData::setCoinNum (clamp > 99 to 0).
// +0x4A u16 flags: bit 0 FieldGameData+0x169, bit 1 +0x13C, bits 2-3 Boost Rush quake short/long (cleared if both set),
// bit 4 *(SaveApplyMgr+0x11), bit 5 FieldGameData+0x160.
// Boost Rush quake calls 0x024CC370 on QuakeMgr when the mode is cBoostRush.
// +0x4C u32 play seconds to FieldGameData+0x138. +0x50 to +0x168.
// +0x51 course type to +0x164 (only 10, 11, 14, else 0xE).
// +0x52 boss bytes to +0x1A4 / +0x1A5 (split on bit7). +0x53 to +0x140.
// +0x54 f32 quake value (Boost Rush only). +0x58 u8 quake power (Boost Rush, clamp 0x13).
// Loading-card WorldCourse text uses MainGame+0x19C / +0x1A8. This function does not write those.
//
// applySaveEntry_ stores a mode in InputMgr+0x514:
// 2 when MainGame+0x88 save record byte0 != 0 (normal save-backed course entry).
// 1 for a challenge with empty record byte0.
// 0 otherwise, and this function is skipped (controller defaults only).
// Modes 1 and 2 always reach here after allocating and copying the 0xE8-byte working buffer.
// A directed open applies save file 1, so byte0 is usually non-zero and this function still runs at course setup.
// What a direct open skips is the world-map path, enterMapFromGameData_ at 0x024C2230.
void sub_0250C3EC(InputMgr* mgr);

class InputMgr
{
    // createInstance()                             Address: 0x0250C348
    // deleteInstance()                             Address: Deleted
    // sInstance                                    Address: 0x101D2DF8
    // SingletonDisposer_::~SingletonDisposer_()    Address: 0x0250E978
    // SingletonDisposer_::sStaticDisposer          Address: 0x101D2DFC
    // SingletonDisposer_::vtbl                     Address: 0x100BED44
    SEAD_SINGLETON_DISPOSER(InputMgr)

public:
    // Address: 0x0250C1A0
    InputMgr();

    sead::Random& getRandom()
    {
        return mRandom;
    }

    u8 getBgmBeatTrg() const
    {
        return mBgmBeatTrg;
    }

    bool isBgmBeatTrg(u8 trg) const
    {
        return trg == mBgmBeatTrg;
    }

    u8 getBgmAccentSign() const
    {
        return mBgmAccentSign;
    }

    bool isBgmAccentSign(u8 mask) const
    {
        return mBgmAccentSign & mask;
    }

    u8 getBgmAccentSignCredit() const
    {
        return mBgmAccentSignCredit;
    }

    u16 getBgmTempo() const
    {
        return mBgmTempo;
    }

    bool isPlayerControllerConnected(s32 player_no) const
    {
        return (mControllerConnectionInfo & (1 << player_no)) != 0;
    }

    bool isFadein() const
    {
        return (mControllerConnectionInfo & (1 << 7)) != 0;
    }

    bool isAreaSceneSwitch() const
    {
        return mIsAreaSceneSwitch;
    }

    bool isInputEnabled() const
    {
        return !isFadein() && !isAreaSceneSwitch();
    }

    // Address: 0x0250CDBC
    // Stores the apply mode at +0x514, then calls sub_0250C3EC for modes 1 and 2.
    // See sub_0250C3EC for the save-byte map. Mode 0 skips that copy.
    void applySaveEntry_(const u32* p_mode_word, void* p_arg, sead::Heap* heap);

    // Address: 0x0250D1EC
    void setupCourseControllers_();

protected:
    u32             _10[(0x52C - 0x10) / sizeof(u32)];
    sead::Random    mRandom;
    bool            mControllersRegistered;
    u16             mBgmTempo;
    u8              mBgmBeatTrg;
    u8              mBgmAccentSign;
    u8              mBgmAccentSignCredit;
    u32             _544[(0x56C - 0x544) / sizeof(u32)];
    u8              mControllerConnectionInfo;
    bool            mIsAreaSceneSwitch;
    u32             _570[(0x57C - 0x570) / sizeof(u32)];
};
static_assert(sizeof(InputMgr) == 0x57C);

#define GAME_RANDOM (InputMgr::instance()->getRandom())
