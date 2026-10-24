#pragma once

#include <course_select/CourseSelectPathNode.h>
#include <layout/ChangePlayerNum.h>

#include <heap/seadDisposer.h>

struct CourseSelectMapPose
{
    s32 world;          // MainGame +0x19C
    s32 section;        // MainGame +0x1A0  (0 or 1; path index = (world<<1)+section)
    s32 node_index;     // MainGame +0x1A4
};
static_assert(sizeof(CourseSelectMapPose) == 0xC);

class CourseSelectMgr   // vtbl Address: 0x10047B48
{
    // createInstance()                             Address: 0x021F8A40
    // deleteInstance()                             Address: Deleted
    // sInstance                                    Address: 0x101CBE14
    // SingletonDisposer_::~SingletonDisposer_()    Address: 0x021FCB3C
    // SingletonDisposer_::sStaticDisposer          Address: 0x101CBE18
    // SingletonDisposer_::vtbl                     Address: 0x10047B38
    SEAD_SINGLETON_DISPOSER(CourseSelectMgr)

public:
    // Address: 0x021F8590
    CourseSelectMgr();
    // Address: 0x021F8AC4
    virtual ~CourseSelectMgr();

    ChangePlayerNum& getChangePlayerNum()
    {
        return mChangePlayerNum;
    }

    // Path table at this+0x18. Named CourseSelectMgr::getPath in headers_names.
    // Address: 0x021F9FC8
    CourseSelectNodePath* getPath(u32 world, u32 section);

    // Path table at this+0x60. Used by map-pose resolve (0x02242A84).
    // Address: 0x021F9FEC
    CourseSelectNodePath* getMapPath(u32 world, u32 section);

    // Address: 0x021C9464
    static CourseSelectPathNode* getNode(CourseSelectNodePath* path, u32 node_index);

protected:
    u32                     _10[2];
    CourseSelectNodePath*   mPathTable0[0x12];   // +0x18  getPath
    CourseSelectNodePath*   mPathTable1[0x12];   // +0x60  getMapPath (pose)
    u32                     _a8[(0x2CC88 - 0xA8) / sizeof(u32)];
    ChangePlayerNum         mChangePlayerNum;
    u32                     _3842c[(0x47820 - 0x3842C) / sizeof(u32)];
};
static_assert(sizeof(CourseSelectMgr) == 0x47824);

// Resolve path node from a world/section/node triple (MainGame map pose layout).
// Address: 0x02242A84
CourseSelectPathNode* getPathNodeFromPose(const CourseSelectMapPose* pose);

// Alias / thunk of getPathNodeFromPose.
// Address: 0x02242AC8
CourseSelectPathNode* getPathNodeFromPose_Thunk(const CourseSelectMapPose* pose);

// Returns node+0x58, or -1 if the node is null.
// Address: 0x02242C70
s32 getCourseSlotFromPose(const CourseSelectMapPose* pose);

// Returns &node->pos (+0x44).
// Address: 0x02242AD0
sead::Vector3f* getPathNodePosFromPose(const CourseSelectMapPose* pose);
