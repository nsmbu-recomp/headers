#pragma once

#include <basis/seadTypes.h>

namespace sead
{
class Heap;
}

class CourseSelectParallelExecuter  // vtbl Address: 0x10058B98 at +0x4020
{
public:
    // Address: 0x02206634
    CourseSelectParallelExecuter();
    ~CourseSelectParallelExecuter();

    // Address: 0x02206788
    void initialize(sead::Heap* heap);

    // Address: 0x02206A80
    void clear();

    // Address: 0x02206B7C
    void executeAll();

protected:
    void*   mItem[0x1000];  // +0x0000
    s32     mItemNum;       // +0x4000

    struct WorkBuffer  // +0x4004
    {
        s32    mCount;
        s32    mCapacity;
        void** mpBuffer;
        void*  mInline[3];
    };
    static_assert(sizeof(WorkBuffer) == 0x18);

    WorkBuffer mWorkBuffer;
    u32        _401c;  // +0x401C
    u32        _4020;  // +0x4020 vtbl
};
static_assert(sizeof(CourseSelectParallelExecuter) == 0x4024);