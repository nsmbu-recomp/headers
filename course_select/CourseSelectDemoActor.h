#pragma once

#include <course_select/CourseSelectActor.h>

class CourseSelectDemoActor : public CourseSelectActor
{
    SEAD_RTTI_OVERRIDE(CourseSelectDemoActor, CourseSelectActor)

public:
    // Address: 0x021D4CB4
    CourseSelectDemoActor(const ActorCreateParam& param);

protected:
    f32 _dc;
    f32 _e0;
    f32 _e4;
    u32 _e8;
    u32 _ec;
    u32 mMapWorld;
    u32 mMapSection;
    u32 mMapParamF8;
    u32 mMapCourseSlot;
    u32 _100;
    u8  _104;
    u8  _105[3];
};
static_assert(sizeof(CourseSelectDemoActor) == 0x108);