#pragma once

#include <basis/seadTypes.h>

#include <state/FStateID.h>

class PauseGame
{
public:
    // Steps the course pause object at 0x101D830C for one frame.
    // When +0xA90 is zero the menu is hidden: the state machine and layout anim step are skipped.
    // +0xA92 is a latch from the pre-step. +0xA94 swaps decide_prev and decide_now for the button update.
    // Address: 0x025FD500
    void executeCourse();

    // Steps the menu pause object at 0x101D7FE0 for one frame.
    // When +0x250 is zero that object's state machine and menu animation are skipped.
    // Address: 0x025F3834
    void execute();

    // Sets or clears bit 0 of the method-tree pause byte on course nodes stored on this object.
    // Plus calls this with set = 1 from 0x0255E8B8. Continue calls it with set = 0 from 0x0255E9B4.
    // Not called from executeCourse. Address: 0x025FE554
    void setCoursePauseNode(u32 set);

    // Sets or clears the player pause nodes at +0x278 and +0x27C and plays a menu button virtual.
    // 0x025FBBE8 calls this with set = 1 or the byte at +0xA92. Address: 0x025FBA74
    void setPlayerPause(u32 set);
    // The button pointer array is at +0x0C. The current index is at +0x10.
    // +0x4C is the cursor index. 0x025BE214 copies it to +0x10 before the cursor is placed.
    // +0x48 is the SelectCursorType for the yellow pause cursor. Type 2 is the full-size TV cursor.
    // The inclusive index range is +0x204 and +0x208.
    // The story menu uses 0 through 2: Continue, Quit, and Change Controller.
    // The button's name pointer is at button+0x54. Row 2 is Pa_PlayStyle_00.
    // The pad word is at +0x50. Down is bit 7, up is bit 6.
    // Plus is bit 11, Touch is bit 12, Decide is bit 13, and Back is bit 14.
    // A set bit 4 of the word at button+0x04 is a button the cursor may land on.
    // The open menu state is 0x10216DB4. Its execute at 0x025FDF98 reads +0x50.
    // A word of 3 at +0x1C enters 0x10216DD4. That state's enter plays the layout anim named Out.
    // Plus or Back (mask 0x4800) changes to 0x10216DF4, which plays the same Out.
    // That state's execute waits for an animation flag, then enters 0x10216D74, which enters 0x10216D94.
    // 0x10216D94 is the controller window. Decide only sets +0xA91, and nothing opens the window from that byte.
    // Enter is Plus. A Settings confirm lets 0x10216DD4 or 0x10216DF4 finish Out, then leaves 0x10216D74 or 0x10216D94.
    // The current state object is the pointer at +0x228. The pending state id is the pointer at +0x224.
    // Closing the overlay sets +0xA90 again. Those three states have to be gone before that, or the controller window opens.
    // The course object has already run executeCourse before execute sees the frame.
    // Opening this menu plays the layout anim named In through 0x02671680 with r4 = 0.
    // The name object is 0x10216E14. The layout pointer is at +0.
    // Draw uses the bytes at +0x1E4, +0x1E6 or +0x1E5, and +0x8.
    // StateID_BackOut         Address: 0x10216DF4
    // initializeState_BackOut Address: 0x025FE4A4
    // executeState_BackOut    Address: 0x025FE4EC
    // finalizeState_BackOut   Address: 0x025FE53C
    // Plus or Back from the open menu enters this state and plays the layout anim named Out.
    // Its execute waits on layout anim 0, then enters 0x10216D74.
    // finalizeState_BackOut clears the draw, shown, and controller-window bytes, then resets the button manager.
    DECLARE_STATE_ID(PauseGame, BackOut)
};

class MethodTreeNode;

// Sets bit 0 of MethodTreeNode::mPauseFlag at node+0x44 on the course-calc node for the active mode.
// paused = 1 when Plus opens the menu; 0 when Continue closes it.
// CourseTask::getGameMode() (CourseTask+0x280) picks the node pointer stored on pause_game:
//   cStory      (+0x264) when MainGame::mReplayFlag at MainGame+0x2C has bit 0x40000000
//   cBoostRush  (+0x234)
//   cChallenge  (+0x254) when the same word has bit 0x10000000, otherwise (+0x23C)
// A set pause bit makes MethodTreeNode_callRecursive_ (0x029FF588) skip the +0x2C delegate and its children, which stops player movement and course-side pad routing.
// The pause menu path then belongs to the nodes at PauseGame+0x4C and +0x50: their pause bits are cleared in the caller so the open-menu state at 0x10216DB4 can read pad input from PauseGame+0x50.
// This function does not write AreaTask fields. The broader pause path also stores 1 at AreaTask+0x730 (mCourseOutKind) to step the course task out.
// Address: 0x025FE554
void PauseGame_setCourseCalcPause(PauseGame* pause_game, u32 paused);

// Aims the yellow SelectCursor at the button at +0x10 and stores that button on the layout slot at +0x48.
// Address: 0x025BE1F0
void sub_025BE1F0(PauseGame* self);

// When +0x1C is 0, copies +0x4C into +0x10, places the cursor, selects the button, and refreshes SelectCursor type +0x48.
// Address: 0x025BE214
void sub_025BE214(PauseGame* self);

// Steps UtilCursorButtonMgr at +0x14 from the pad, touch pointer, and decide edges. PauseGame::execute finishes here.
// Address: 0x025BE30C
void sub_025BE30C(PauseGame* self, u8 decide_prev, u8 decide_now);
