#pragma once

#include <basis/seadTypes.h>

#include <nw/snd/snd_SoundHandle.h>

class SndSpeakerMgr
{
public:
    // sInstance                                    Address: 0x101E7D0C
    static SndSpeakerMgr* instance()
    {
        return sInstance;
    }

    // Address: 0x029C37BC
    void setRemoteSend(nw::snd::SoundHandle* p_handle, nw::snd::OutputLine line_flag, u32 param);

private:
    static SndSpeakerMgr* sInstance;
};
