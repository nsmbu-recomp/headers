#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>

// World-map path node (USA v1.3.0).
// Size 0x68; indexed from a path object as path+0x10 + index*0x68 (see CourseSelectMgr::getNode).
//
// Identity:
//   Prefer the name string at +0x00 (e.g. "W101" = pack world 1 course 1).
//   +0x58 is the course/slot id returned by getCourseSlotFromPose (0x02242C70).
//   +0x50 / +0x54 are NOT reliable world/course numbers (often 0,0 on W1S0 and W101).

struct CourseSelectPathNode
{
    const char*     name;           // +0x00  pointer to node name ("W101", "W1S0", ...)
    u8              _04[0x40];
    sead::Vector3f  pos;            // +0x44
    s32             _50;            // +0x50  do not treat as world
    s32             _54;            // +0x54  do not treat as course
    s32             course_slot;    // +0x58  course/slot id (classify with getCourseSelectNodeType)
    s32             node_index;     // +0x5C  looks like node index in path
    u8              _60[8];
};
static_assert(sizeof(CourseSelectPathNode) == 0x68);

// Path blob holding an array of CourseSelectPathNode starting at +0x10.
// Pointers live in CourseSelectMgr at +0x18 and +0x60; map pose uses +0x60.
struct CourseSelectNodePath
{
    u8                      _00[0x10];
    CourseSelectPathNode    node[1];    // variable length; index with getNode
};
