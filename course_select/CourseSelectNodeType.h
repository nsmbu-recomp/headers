#pragma once

#include <basis/seadTypes.h>

// Classification of CourseSelectPathNode::course_slot (+0x58).
// Used by CourseSelectPlayer::create_ after getCourseSlotFromPose (0x02242C70).
//
// Type 0 = regular course ids 0..11 (f_024D37A0).
// Type 2 = ids 20 / 21 (f_024D37EC) — required for the create_ path that
//          compares player +0xF0/+0xFC to MainGame pose; regular courses
//          fail that check and take L_02270268 (often ActorMgr::createLater).

enum CourseSelectNodeType
{
    cCourseSelectNodeType_Course = 0,   // ids 0..11
    cCourseSelectNodeType_1      = 1,   // id 19
    cCourseSelectNodeType_2      = 2,   // ids 20, 21
    cCourseSelectNodeType_3      = 3,   // ids 22, 23
    cCourseSelectNodeType_4      = 4,   // ids 24..30 or 46..53
    cCourseSelectNodeType_5      = 5,   // id 36
    cCourseSelectNodeType_6      = 6,   // id 37
    cCourseSelectNodeType_7      = 7,   // ids 41, 42
    cCourseSelectNodeType_8      = 8,   // ids 12..16
    cCourseSelectNodeType_9      = 9,   // ids 31..33 or 54..56
    cCourseSelectNodeType_Other  = 10
};
static_assert(sizeof(CourseSelectNodeType) == 4);

// Address: 0x024D37A0
bool isCourseSelectCourseNo(u8 course_no);
// Address: 0x024D37D4
bool isCourseSelectCourseNo_19(u8 course_no);
// Address: 0x024D37EC
bool isCourseSelectCourseNo_20_21(u8 course_no);
// Address: 0x024D380C
bool isCourseSelectCourseNo_22_23(u8 course_no);
// Address: 0x024D382C
bool isCourseSelectCourseNo_41_42(u8 course_no);
// Address: 0x024D384C
bool isCourseSelectCourseNo_Type4(u8 course_no);
// Address: 0x024D37B8
bool isCourseSelectCourseNo_Type8(u8 course_no);
// Address: 0x024D38BC
bool isCourseSelectCourseNo_Type9(u8 course_no);

// Address: 0x021EF6C8
CourseSelectNodeType getCourseSelectNodeType(s32 course_slot);
