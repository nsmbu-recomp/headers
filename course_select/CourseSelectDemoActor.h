#pragma once

#include <course_select/CourseSelectActor.h>

// Course-select map demo actor: stores overworld map indices from create params and gates demo draw via profile checks.
class CourseSelectDemoActor : public CourseSelectActor
{
    // getRuntimeTypeInfoStatic()::typeInfo initialization guard variable   Address: 0x101EA3D0
    // getRuntimeTypeInfoStatic()::typeInfo                                 Address: 0x101EA3F4
    SEAD_RTTI_OVERRIDE(CourseSelectDemoActor, CourseSelectActor)

public:
    // Address: 0x021D4CB4
    CourseSelectDemoActor(const ActorCreateParam& param);

protected:
    // Address: 0x021D5838
    virtual ~CourseSelectDemoActor();

    // Address: 0x021D4D60
    virtual bool preExecute_();
    // Address: 0x021D4DB8
    virtual bool preDraw_();

    // Address: 0x021D5948
    virtual u8 getDemoFlag() const;
    // Address: 0x021D5950
    virtual void setDemoFlagOn();
    // Address: 0x021D595C
    virtual void setDemoFlagOff();

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