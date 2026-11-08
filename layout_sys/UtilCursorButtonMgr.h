#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>

class UtilCursorButtonMgr
{
public:
    // Address: 0x02681FC4
    UtilCursorButtonMgr();

    // Calls virtual function +0xF4 on every button in the list at +0x10.
    // That call refreshes the button hit rectangle.
    // decide_prev and decide_now are the decide edges for this frame.
    // pointer_pos is the cursor pointer in layout space.
    // The path with no pointer passes the default position at 0x105FA740.
    // When the button at +0x1C differs from +0x18, execute calls two virtuals on button+0x1C.
    // Offset 0x1C clears the previous button. Offset 0x14 selects the new button.
    // It then calls 0x02677A38 on the new button. That plays the cursor sound unless +0x98 or +0x7C is set.
    // The helper at 0x02682594 crashes when the previous button at +0x18 is null.
    // Address: 0x02682608
    void execute(u8 decide_prev, u8 decide_now, sead::Vector2f* pointer_pos);

protected:
    u32         mSeBackOutputLine;  // CursorButtonBase::OutputLineFlag
    const char* mSeBack;
    u32         mExecStep;
    u32         _c[(0x34 - 0xC) / sizeof(u32)];
};
static_assert(sizeof(UtilCursorButtonMgr) == 0x34);
