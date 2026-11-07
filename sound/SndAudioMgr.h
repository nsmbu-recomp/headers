#pragma once

#include <sound/AudAudioMgr.h>
#include <sound/SndItemID.h>

#include <heap/seadDisposer.h>
#include <math/seadVector.h>

#include <nw/snd/snd_SoundArchive.h>
#include <nw/snd/snd_SoundHandle.h>

// Method table at +0x3D0 is 0x1017C814. An earlier note wrote 0x1018C814.
// Entries are 8 bytes with the function pointer at +4:
// +0x04 = 0, +0x0C = initialize (0x029B41AC), +0x14 = calc (0x029B4FFC),
// +0x1C = the deleted vf1C (the panic 0x02AFA5E8), +0x24 = startSoundImpl (0x029B6B10).
// The ctor 0x029B393C allocates 0x3D4 bytes and stores that table at +0x3D0.
// AudAudioMgr is not polymorphic (ctor 0x029B1AAC sets no vptr), so +0x3D0 is the only method table.
//
// Sound-info table (sead::AudioPlayer vtable at +0, nw::snd::SoundArchivePlayer / SoundStartable at +4):
// count at SoundStartable+0x18 (player+0x1C), table pointer at +0x1C (player+0x20), entry stride 0x78.
// GetSoundInfo is 0x02ADB9C0: table + id * 120.
// Ctor 0x02ADAA34 zeroes count and table. Shutdown 0x02ADB714 clears them.
// Setup carves the table in 0x02ADAE50, reached from SoundArchivePlayer Setup 0x02ADB338
// through 0x02ADB530, 0x02ADB634, and AudioPlayerCafe buffer setup 0x029E6C38 / 0x029E8324.
// The bl 0x02ADB338 at 0x02ADB580 is inside 0x02ADB530.
// AudAudioPlayer::initialize (0x029B21A0) is a no-op branch to 0x029E6EA0 (blr). Nothing calls it.
// It appears only as a method-table slot at rodata 0x1017C1BC.
// loadData, startSound, and startSoundImpl do not install the table.
// startSound has one static caller, startSystemSe, which gameplay reaches.
// The bctrl at 0x029B5460 in startSound is startSoundImpl.
// 0x029E8324 is the first {0, fn} slot in rodata 0x1017C284, and also at 0x1018DA04+0x18.
// 0x1017C1A4 is AudAudioPlayer's vtable. No .text bl targets 0x029E8324.
// The sound-info table is carved only after 0x029E8324 -> 0x029E6C38 -> ... -> 0x02ADB338.
// Disassembly shows Setup before any static startSound call site.
// It does not show runtime order against a table-dispatched init after a wiped image.
// The table pointer is stored before Setup finishes, so an AX callback or startSoundImpl that runs before 0x02ADB338 returns can see a null table.
// Cold boot still relies on AudAudioPlayer construction before course gameplay SE.
class SndAudioMgr : public AudAudioMgr  // vtbl Address: 0x1017C814
{
    SEAD_SINGLETON_DISPOSER(SndAudioMgr)

public:
    struct Arg;

public:
    // Address: 0x029B41AC
    // Does not install the sound-info table. See the class note.
    virtual void initialize(const Arg& arg);
    // Address: 0x029B4FFC
    virtual void calc();
    // Address: Deleted
    virtual void vf1C();
    // Address: 0x029B6B10
    // Virtual slot +0x24 of the table at +0x3D0.
    // A null sound-info table faults here. The table is carved by SoundArchivePlayer Setup (0x02ADB338), not by this function.
    virtual bool startSoundImpl(nw::snd::SoundHandle* p_handle, const char* label);
    // ...

    // Address: 0x029B3BA8
    nw::snd::SoundArchive* getSoundArchive();

    // Address: 0x029B3D8C
    bool isSndPlaying(const char* label);

    // Address: 0x029B54C0
    bool startSystemSe(const char* label, nw::snd::OutputLine line_flag = nw::snd::OUTPUT_LINE_MAIN);

    // Address: 0x029B5434
    // One static caller: startSystemSe at 0x029B5520.
    // The bctrl at 0x029B5460 is startSoundImpl. r3 = this, r4 = handle, r5 = label.
    // Does not install the sound-info table.
    bool startSound(nw::snd::SoundHandle* p_handle, const char* label, nw::snd::OutputLine line_flag = nw::snd::OUTPUT_LINE_MAIN);

    // Address: 0x029B5934
    void startDrcTouchSound(const sead::Vector2f& world_pos, u32 type);

    // Address: 0x029B7548
    // Does not install the sound-info table.
    bool loadData(SndItemID item_id);

private:
    u32 _1C[(0x3D0 - 0x1C) / sizeof(u32)];
    const void* mpSoundStartable;  // +0x3D0
};
static_assert(sizeof(SndAudioMgr) == 0x3D4);
