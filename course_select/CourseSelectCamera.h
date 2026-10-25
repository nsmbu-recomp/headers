#pragma once

#include <course_select/CourseSelectDemoActor.h>
#include <course_select/CourseSelectMgr.h>

class CourseSelectCamera : public CourseSelectDemoActor
{
public:
    // Address: 0x0227C858
    CourseSelectPathNode* findFocusPathNode(u32 search_mode);
    // Address: 0x0227CA20
    CourseSelectPathNode* findFocusPathNodeCheckpoint();
    // Address: 0x0227D310
    CourseSelectPathNode* findFocusPathNodeCourse();

    // Address: 0x0227CCDC
    void applyFocusFromCheckpointSearch();
    // Address: 0x0227E284
    void applyFocusFromCourseSearch();

protected:
    void copyFocusFromNode_(const CourseSelectPathNode* node, bool copy_view);
    void updateMapTitle_();

    u32                 _108[(0x12C - 0x108) / sizeof(u32)];
    s32                 mFocusWorldTag;     // +0x12C  path node +0x50 (title key; not map world)
    s32                 mFocusCourseTag;    // +0x130  path node +0x54
    s32                 mFocusNodeIndex;    // +0x134  path node +0x5C
    u8                  _138[0x160 - 0x138];
    s32                 mFocusSearchPhase;    // +0x160
    u8                  _164[0x1B8 - 0x164];
    f32                 mFocusViewY;        // +0x1B8
};
