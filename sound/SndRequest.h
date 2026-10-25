#pragma once

#include <basis/seadTypes.h>

class ResMgr;

class SndRequest
{
public:
    void*   mpActor;
    void*   mpSub;

    // Address: 0x024BD6EC
    static void queueCourseUnitLoad(SndRequest* request, s32 match_count, u32 use_rdash_label);
};

// Address: 0x029D34A8
void SndQueue_pushRequest(ResMgr* res_mgr, SndRequest* request, const char* label, u32 param0, u32 param1);
