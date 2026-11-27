#pragma once

#include <course_select/CourseSelectDemoActor.h>

class CourseSelectObjActor : public CourseSelectDemoActor  // size 0x10C
{
    SEAD_RTTI_OVERRIDE(CourseSelectObjActor, CourseSelectDemoActor)

public:
    // Address: 0x02201C04
    CourseSelectObjActor(const ActorCreateParam& param);

    s32 queryMapStateA();
    s32 queryMapStateB();
    s32 queryMapStateC();
    s32 queryMapStateD();
    s32 queryMapStateE();

protected:
    s32     _108;
};
static_assert(sizeof(CourseSelectObjActor) == 0x10C);