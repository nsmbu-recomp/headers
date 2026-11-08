#pragma once

#include <input/SysControllerWrapper.h>
#include <player/PlayerEnum.h>

#include <framework/seadCalculateTask.h>
#include <framework/seadTaskMgr.h>
#include <layer/aglRenderInfo.h>
#include <math/seadBoundBox.h>

class AreaTask : public sead::CalculateTask // vtbl Address: 0x100B6984
{
    // setInstance_()                               Address: 0x024B5378
    // deleteInstance()                             Address: Deleted
    // sInstance                                    Address: 0x101D1598
    // SingletonDisposer_::~SingletonDisposer_()    Address: 0x024B5228
    SEAD_TASK_SINGLETON_DISPOSER(AreaTask)

public:
    // Address: 0x024B5398
    AreaTask(const sead::TaskConstructArg& arg);
    // Address: 0x024B5254
    virtual ~AreaTask();

    sead::BoundBox2f& getBound() { return mBound; }
    const sead::BoundBox2f& getBound() const { return mBound; }

    u32 getLoopType() const { return mLoopType; }
    // Address: 0x024B5B20
    void setLoopType();

    // Address: 0x024B814C
    void setCourseOut();

    // Address: 0x024B7808
    void requestCourseOut_Down();
    // Address: 0x024B77DC
    void requestCourseOut_Normal();
    // Address: 0x024B8158
    void requestCourseOut_Secret();
    // Address: 0x024B8184
    void requestCourseOut_TreasureChest();
    // Address: 0x024B81AC
    void requestCourseOut_TreasureChestFail();
    // Address: 0x024B81D4
    void requestCourseOut_Subject();

    // After NextGoto lookup: CourseInfo enter-type 3, then setCourseOut.
    // Site 0x024B8324 is immediately before setCourseOut.
    // Address: 0x024B82A4
    void prepareCourseOutEnter(u32 next_goto_key);

    // Guessed name.
    // Course tile callback stored on this task. Runs only when the step in r5 is 0.
    // RenderInfo arrives in r6. Loads the object at 0x101EAFE8 and tails to 0x0269018C.
    // Address: 0x024B47A8
    void drawCourseTiles(s32, s32 step, const agl::lyr::RenderInfo& render_info);

    // Guessed name.
    // Second course tile callback. Same step check. Tails to 0x02690458.
    // Address: 0x024B47C8
    void drawCourseTilesSecond(s32, s32 step, const agl::lyr::RenderInfo& render_info);

    // Address: 0x024B84A8
    void drawLayer3D(const agl::lyr::RenderInfo& render_info);
    // Address: 0x024B8B98
    void debugDraw(const agl::lyr::RenderInfo& render_info);

    // Address: 0x024B8034
    f32 getLoopPosX(f32 x);

    // Address: 0x025CF020
    static u32 getCourseOutHudFlag();

private:
    u8                      _c9;
    bool                    mIsPrepareDone;
    bool                    mIsDrawMethodReady;
    SysControllerWrapper    mControllerWrapper[cPlayerNum];
    sead::BoundBox2f        mBound;
    u32                     mLoopType;
    u32                     mCourseOutKind;         // +0x730  3 = normal course-out request
    u8                      _734[(0x74D - 0x734)];
    bool                    mIsCourseOut;           // +0x74D  set by setCourseOut
    u8                      _74e[(0xBE4 - 0x74E)];
};
static_assert(sizeof(AreaTask) == 0xBE4);
