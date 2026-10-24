#pragma once

#include <course_select/CourseSelectDemoActor.h>

class CourseSelectObjActor : public CourseSelectDemoActor  // size 0x10C
{
    SEAD_RTTI_OVERRIDE(CourseSelectObjActor, CourseSelectDemoActor)

public:
    // Address: 0x02201C04
    CourseSelectObjActor(const ActorCreateParam& param);

    // Address: 0x02201C70
    s32 queryMapStateA();
    // Address: 0x02201C84
    s32 queryMapStateB();
    // Address: 0x02201C90
    s32 queryMapStateC();
    // Address: 0x02201C9C
    s32 queryMapStateD();
    // Address: 0x02201CA8
    s32 queryMapStateE();

protected:
    s32     _108;
};
static_assert(sizeof(CourseSelectObjActor) == 0x10C);
