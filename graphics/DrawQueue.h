#pragma once

#include <basis/seadTypes.h>
#include <graphics/Model.h>
#include <thread/seadCriticalSection.h>
#include <utility/Angle.h>
#include <utility/Mtx.h>

// Guessed name.
// A pending draw-queue entry. While active, mRecycleLink stores the layer node id
// that sub_024D6EAC uses when pushing into RenderObjRenderMgr. After draining the
// item is stored on the list free chain through the same word.
struct DrawItem
{
    u32                     mLayerNode;         // +0x00
    f32                     mSortKey0;          // +0x04
    f32                     mSortKey1;          // +0x08
    f32                     mSortKey2;          // +0x0C
    u8                      _10[0x0C];
    Angle                   mAngleX;            // +0x1C
    Angle                   mAngleY;            // +0x20
    Angle                   mAngleZ;            // +0x24
    Model*                  mpModel;            // +0x28
};
static_assert(offsetof(DrawItem, mpModel) == 0x28);

// Guessed name.
// PtrArray-shaped list head used at ModelDrawMgr+0x268, +0xE7C, +0x1A90, and +0x26A4.
// +0x0C keeps recycled DrawItem nodes.
struct PendingDrawList
{
    s32                     mCount;
    u32                     _04;
    DrawItem**              mBuffer;
    DrawItem*               mpFree;
};

// Address: 0x029F1F4C
// Erases count slots from the pointer buffer at list+0x8 and decrements list+0x0.
void sub_029F1F4C(PendingDrawList* list, s32 index, s32 count);

// Guessed name.
// Registered as a draw callback beside the Capture layer name.
// The object keeps model lists at +0x268, +0xE7C, +0x1A90, and +0x26A4.
class ModelDrawMgr
{
public:
    // Guessed name.
    // Locks the CriticalSection at this+0x35D4. When *flag is 0, drains the four
    // pending lists in priority order. Vanilla code reads node+0x28 and uses the
    // Model* immediately with no null check.
    // Address: 0x024D752C
    void buildQueues(const u32* flag);

private:
    // Address: 0x024D6F5C
    void buildOpaqueQueue_();
    // Address: 0x024D7088
    void buildMiiQueue_();
    // Address: 0x024D71A4
    void buildMultiQueue_();
    // Address: 0x024D72C0
    void buildReflectionQueue_();
};