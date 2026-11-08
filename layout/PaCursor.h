#pragma once

#include <game/SelectCursorType.h>
#include <input/SysControllerWrapper.h>
#include <layout_sys/UtilCursorButtonMgr.h>
#include <state/FStateMgr.h>

#include <container/seadSafeArray.h>
#include <prim/seadSafeString.h>

class PaCursor  // vtbl Address: 0x100D6B34
{
public:
    static const s32 cButtonMax = 41;

public:
    // Address: 0x025F8024
    PaCursor();
    // Address: 0x025F8230
    virtual ~PaCursor();

    // Steps this cursor for one frame.
    // A set byte at +0x25C runs the cursor state, then the update at 0x025F8394, then the bookkeeping at 0x025F8514.
    // A clear byte at +0x25C skips that state.
    // A clear +0x25D on that path returns before the button manager, so the yellow cursor stays put.
    // A set +0x25D updates the button manager at +0x24 from the pointer, or from the pad when the pointer is idle.
    // Bookkeeping at 0x025F9400 clears +0x25C and +0x25E when the word at +0x26C for the current index is 0 or 2.
    // Any other word calls 0x02682CD0 and then sets +0x268. A set +0x268 skips that check on later frames.
    // Normal buttons leave the word at 0. triggerDecide at 0x025F8788 sets +0x25F and writes the word.
    // Address: 0x025F85B8
    void execute();

    bool isNoPadInput() const
    {
        return mIsNoPadInput;
    }

    // Address: 0x025F8788
    void triggerDecide();

    void resetDecideTrig()
    {
        mIsDecideTrig = false;
    }

protected:
    FStateMgr<PaCursor>                 mStateMgr;
    // +8 is the step. Step 2 moves the yellow cursor when +0x1C differs from +0x18.
    // The drawn cursor follows the button at +0x3C. Callers at 0x025F9184 and 0x025F9494 pass that button to SelectCursor.
    // execute is 0x02682608.
    UtilCursorButtonMgr                 mButtonMgr;
    SysControllerWrapper                mController;
    sead::SafeArray<u8, cButtonMax>     _1ec;
    sead::SafeArray<u8, cButtonMax>     _215;
    sead::SafeString                    mParentName;
    sead::Vector2f                      mPointerPos;
    s32                                 mButtonIdx1;        // Current, +0x250
    // Hover execute copies this into mButtonIdx1 at 0x025F95A4 and again at 0x025F964C.
    // A move that writes only the current index is put back on the next hover frame.
    s32                                 mButtonIdx2;        // Previous, +0x254
    SelectCursorType                    mSelectCursorType;
    bool                                mIsDecideAnime;     // Maybe?
    bool                                _25d;
    // With the fields above, this is +0x25E.
    // CourseSelectMenu at 0x025A5420 handles the cursor index only while this byte is clear.
    bool                                mIsNoPadInput;
    bool                                mIsDecideTrig;
    bool                                _260;
    bool                                _261;
    bool                                mIsDpadTrig;
    bool                                _263[9];
    // Bookkeeping reads the live words at +0x26C, one per button. 0 or 2 drops the pad.
    sead::SafeArray<u32, cButtonMax>    mButtonState;
};
static_assert(sizeof(PaCursor) == 0x314);
