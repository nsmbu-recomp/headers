#pragma once

#include <audio/cafe/seadAudioPlayerCafe.h>

class AudAudioPlayer : public sead::AudioPlayerCafe
{
public:
    AudAudioPlayer();
    virtual ~AudAudioPlayer();

    // Address: 0x029B21A0
    // Branches to 0x029E6EA0, which is blr. Nothing calls it.
    // The PC appears only as a method-table slot at rodata 0x1017C1BC.
    void initialize() override;
    void finalize() override;
    void calc() override;
};
static_assert(sizeof(AudAudioPlayer) == sizeof(sead::AudioPlayerCafe));
