#pragma once

#include <course_select/CourseSelectActor.h>

class CourseSelectDemoActor : public CourseSelectActor  // size 0x108
{
    SEAD_RTTI_OVERRIDE(CourseSelectDemoActor, CourseSelectActor)

public:
    // Address: 0x021D4CB4
    CourseSelectDemoActor(const ActorCreateParam& param);

    s32 getMapWorld() const { return mMapWorld; }
    s32 getMapSection() const { return mMapSection; }
    s32 getMapParamF8() const { return mMapParamF8; }
    s32 getMapCourseSlot() const { return mMapCourseSlot; }

protected:
    f32     _dc;
    f32     _e0;
    f32     _e4;
    u32     _e8;
    u32     _ec;
    s32     mMapWorld;          // +0xF0  compared to MainGame+0x19C at create_
    s32     mMapSection;        // +0xF4
    s32     mMapParamF8;        // +0xF8  often 0; written -1 during some setups
    s32     mMapCourseSlot;     // +0xFC  must match node+0x58 / getCourseSlotFromPose
    u32     _100;
    u8      _104;
    u8      _105[3];
};
static_assert(sizeof(CourseSelectDemoActor) == 0x108);
