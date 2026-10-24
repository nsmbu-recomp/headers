#pragma once

#include <course_select/CourseSelectObjActor.h>

class AnimModel;

// Profile 854. create_ at 0x0226FBC4 reads MainGame map pose at site 0x0226FD14.
class CourseSelectPlayer : public CourseSelectObjActor  // size 0x120
{
    SEAD_RTTI_OVERRIDE(CourseSelectPlayer, CourseSelectObjActor)

public:
    // Address: 0x0226FA30
    CourseSelectPlayer(const ActorCreateParam& param);

    // Address: 0x0226FBC4
    virtual Result create_();

protected:
    // Address: 0x0226FACC
    void updateModelMtx_();
    // Address: 0x0226FB80
    void playModelAnm_();

protected:
    AnimModel*      mpAnimModel;    // +0x10C
    sead::Vector3f  mModelPos;      // +0x110
    u8              _11c;
    u8              _11d[3];
};
static_assert(sizeof(CourseSelectPlayer) == 0x120);
