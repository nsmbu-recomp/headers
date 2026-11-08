#pragma once

#include <heap/seadDisposer.h>

class SndBgmMgr
{
    SEAD_SINGLETON_DISPOSER(SndBgmMgr)

public:
    SndBgmMgr();
    ~SndBgmMgr();

    // Returns whether id is below cGameBgmNum (29).
    // Address: 0x029B83C8
    bool isGameBgm(s32 id);

    // Guessed address. This and getGameControlBgmID both call isGameBgm, then return a name.
    // Address: 0x029B8448
    const char* getGameBgmID(s32 id);

    // Guessed address. See getGameBgmID.
    // Address: 0x029B84D8
    const char* getGameControlBgmID(s32 id);

    // Address: 0x029B83D8
    bool shouldHurryUp();

    // Guessed name.
    // r4 is the layer. Layer 17 stores r5 at mStreamID when isGameBgm(r5) is true.
    // Callers load this from 0x101E7CA8. The fader layers are 17 and 29.
    // Also reads SndAudioMgr::sInstance and compares the label STRM_BGM_MENU.
    // Address: 0x029B85C8
    void updateForLayer(s32 layer, u32 arg);

    // ...

private:
    s32         mStreamID;
    const char* mBgmID;
    const char* mControlBgmID;
    u32         mSoundType; // nw::snd::SoundArchive::SoundType
    u32         _20;
    u32         _24;
    u8          _28;
    u8          _29;
    u8          _2A;
    u8          _2B;
    u32         _2C;
    u32         _30;
    u32         _34;
    const char* _38;
    const char* _3c;
    f32         _40;
    f32         _44;
    u8          _48;
    u8          _49;
    u8          _4A;
    u8          _4B;
    u32         _4C;
    u32         _50;
    u32         _54;
    const char* _58;
    u32         _5C;
    s32         _60;
    u32         _64;
    u32         _68;
    u32         _6C;
    f32         _70;

    static const u32 cGameBgmNum = 29;

    struct Bgm
    {
        const char* name;
        u32 _4;
    };
    static_assert(sizeof(Bgm) == 8);

    static const Bgm cGameBgm_Normal[cGameBgmNum + 1];
    static const Bgm cGameBgm_Fast[cGameBgmNum + 1];

    static const Bgm cGameControlBgm_Normal[cGameBgmNum + 1];
    static const Bgm cGameControlBgm_Fast[cGameBgmNum + 1];
};
static_assert(sizeof(SndBgmMgr) == 0x74);
