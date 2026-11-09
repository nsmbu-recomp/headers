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
    // 0x026829A4 sets bit 2 of +0x28 only when the step at +8 is 0. A later press has to clear that step first.
    // That bit calls virtual +0x24 on the button at +0x18, and only when the byte at button+0x84 is 0.
    // That virtual plays the click only when the float at +0xC of the anim at button+0x30 is 0.
    // It then starts the decide anim at button+0x6C. Virtual +0xAC sets the speed and does not rewind the frame.
    // 0x02676E74 ends with virtual +0xCC on that decide anim. That call sets the anim speed to 0.
    // A later decide leaves button+0x84 set, so the click flag is dropped and 0x02677550 does not run.
    // That later press has to restore the idle decide anim at button+0x6C or the press does not replay.
    // 0x02677550 also returns without a sound when the low byte of the id at button+0xA4 is 0.
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
