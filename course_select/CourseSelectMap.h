#pragma once

#include <graphics/Model.h>

#include <heap/seadDisposer.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>

namespace agl { namespace lyr {
class Layer;
} }

class MapModel
{
public:
    // Address: 0x022961AC
    MapModel(sead::Heap* heap, const sead::SafeString& name);

    // Address: 0x02296B38
    void initialize(u32 world, u32 index);

    // Address: 0x02297A24
    void draw() const;

    Model* getModel() const
    {
        void* const* pp_holder = reinterpret_cast<void* const*>(
            reinterpret_cast<const u8*>(this) + 0x04);

        return static_cast<Model*>(*reinterpret_cast<void**>(*pp_holder));
    }
};

class CourseSelectParallelExecuter
{
public:
    // Address: 0x02206634
    CourseSelectParallelExecuter();
    // Address: 0x022066DC
    virtual ~CourseSelectParallelExecuter();

    // Address: 0x02206788
    void initialize(sead::Heap* heap);

    // Address: 0x02206A80
    void clear();

    // Address: 0x02206B7C
    void executeAll();

protected:
    void*   mItem[0x1000];      // +0x0000
    s32     mItemNum;           // +0x4000

    struct WorkBuffer           // +0x4004
    {
        s32     mCount;
        s32     mCapacity;
        void**  mpBuffer;
        void*   mInline[3];
    };
    static_assert(sizeof(WorkBuffer) == 0x18);

    WorkBuffer  mWorkBuffer;
    u32         _401c;          // +0x401C
    const void* _4020;          // +0x4020
};
static_assert(sizeof(CourseSelectParallelExecuter) == 0x4024);

class CourseSelectMap
{
    // createInstance()                              Address: 0x021F55F8
    // sInstance                                     Address: 0x101CBD34
    // SingletonDisposer_::sStaticDisposer           Address: 0x101CBD38
    // SingletonDisposer_::vtbl                      Address: 0x10047870
    SEAD_SINGLETON_DISPOSER(CourseSelectMap)

public:
    // Address: 0x021F5548
    // Sets +0xA0 to 1 and the model-node offset of each list to 0x72C.
    CourseSelectMap();
    // Address: 0x021F5678
    virtual ~CourseSelectMap();

    // Address: 0x021F56CC
    // Formats CS_W<world+1> and course_select/<name>.szs.
    // Index 0 checks the plain archive, then the suffixed name.
    // A higher index checks only CS_W<world+1><a+index>.
    // Builds a MapModel (0x022961AC) with a null heap and calls initialize(world, index) (0x02296B38).
    MapModel* loadModel(u32 world, u32 index);

    // Address: 0x021F5800
    void getBoneWorldMatrix(u32 world, u32 index, const char* p_bone_name, sead::Matrix34f* p_mtx) const;

    // Address: 0x021F59A8
    void getBoneWorldPos(sead::Vector3f* p_pos, u32 world, u32 index, const char* p_bone_name) const;

    // Address: 0x021F6C14
    // Runs the whole map model setup:
    // 1. mExecuter.initialize(nullptr)
    // 2. For each world 0..8, loadModel(world, index) until it returns null. Link each model and bump the count.
    // 3. 0x021F5D20
    // 4. For each world and model, 0x021FAC24(CourseSelectMgr::instance(), model, world, index). That walks the list from +0x04.
    // 5. 0x021F62E0
    // 6. For each world, 0x021F6AEC(this, world, MainGame::sInstance[0x2F8 + world*4], 1.0f, 1)
    // 7. 0x021F6B3C
    // 8. 0x0229B44C on the first node of list 1
    // 9. For each world and model, 0x0229A4A8
    void initialize();

    // Address: 0x021F6FE8
    // Returns early when CourseSelectTask+0xDC9 is not 0.
    // Otherwise clears the executer, queues every list node (cap 0x1000), runs executeAll, and calls 0x0228A948(*(0x101CD0C0)).
    void calc();

    // Address: 0x021F7114
    // Sets a renderer layer, draws the lists in the order 8, 5, 6, 0, 1, 4, 3, 7, 2 (0x10047808), then resets the layer.
    void draw(agl::lyr::Layer* p_layer);

protected:
    // Nine lists start at +0x10. Each is 0x10 bytes.
    // +0x00 is the head. +0x04 is the walk start. +0x08 is the count. +0x0C is the model node offset (0x72C).
    // A list node is (u8*)model + mOffset.
    // 0x029F1A50 links a node at the head.
    // Each node keeps the list pointer at +0x04 as the terminator, so iteration starts at the list +0x04 field and follows node +0x04.
    struct ModelList            // +0x10, ctor Address: 0x021F76FC
    {
        void*   mHead;          // +0x00
        void*   mTail;          // +0x04 walk start. The node stores this pointer as the terminator.
        s32     mCount;         // +0x08
        s32     mOffset;        // +0x0C
    };
    static_assert(sizeof(ModelList) == 0x10);

    ModelList                   mModelList[9];  // +0x10
    bool                        _a0;            // +0xA0. 1 after the ctor.
    CourseSelectParallelExecuter mExecuter;     // +0xA4
};
static_assert(sizeof(CourseSelectMap) == 0x40C8);
