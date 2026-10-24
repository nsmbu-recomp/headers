#pragma once

#include <actor/ActorBase.h>
#include <math/seadVector.h>

class CourseSelectActor : public ActorBase
{
    SEAD_RTTI_OVERRIDE(CourseSelectActor, ActorBase)

public:
    // Address: 0x021B2310
    CourseSelectActor(const ActorCreateParam& param);

    sead::Vector3f& getPos() { return mPos; }
    const sead::Vector3f& getPos() const { return mPos; }

protected:
    // Address: 0x021B2528
    virtual bool preExecute_();
    // Address: 0x021B2658
    virtual bool preDraw_();

protected:
    sead::Vector3f  mPos;           // +0x50
    sead::Vector3f  mPosPrev;       // +0x5C
    sead::Vector3f  mScale;         // +0x68
    sead::Vector3f  _74;            // +0x74
    sead::Vector3f  _80;            // +0x80
    sead::Vector3f  _8c;            // +0x8C
    sead::Vector3f  _98;            // +0x98
    sead::Vector3f  _a4;            // +0xA4
    u32             _b0;
    u32             _b4;
    u32             _b8;
    u32             _bc;
    u32             _c0;
    u32             _c4;
    f32             _c8;
    f32             _cc;
    f32             _d0;
    f32             _d4;
    u8              _d8;
    u8              _d9[3];
};
static_assert(sizeof(CourseSelectActor) == 0xDC);
