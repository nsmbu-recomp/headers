#pragma once

#include <actor/ActorCreateParam.h>

// Guest object. No host vtable: the guest heap pointer lives at +0.
class CourseSelectActor
{
public:
    // Address: 0x021B2310
    CourseSelectActor(const ActorCreateParam& param);

    // Address: 0x021B2528
    bool preExecute_();
    // Address: 0x021B2658
    bool preDraw_();
};
