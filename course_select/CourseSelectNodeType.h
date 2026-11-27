#pragma once

#include <basis/seadTypes.h>

enum CourseSelectNodeType
{
    cCourseSelectNodeType_Course = 0,
    cCourseSelectNodeType_1      = 1,
    cCourseSelectNodeType_2      = 2,
    cCourseSelectNodeType_3      = 3,
    cCourseSelectNodeType_4      = 4,
    cCourseSelectNodeType_5      = 5,
    cCourseSelectNodeType_6      = 6,
    cCourseSelectNodeType_7      = 7,
    cCourseSelectNodeType_8      = 8,
    cCourseSelectNodeType_9      = 9,
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