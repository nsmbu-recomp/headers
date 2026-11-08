#pragma once

class PauseGame
{
public:
    // Steps the in-level pause menu for one frame.
    // The course pause object is the pointer at 0x101D830C.
    // 0x025FD500 steps that object. A zero byte at +0xA90 skips its state machine.
    // This function steps the other object, the pointer at 0x101D7FE0.
    // A zero byte at +0x250 skips that object's state machine and its menu animation.
    // Either step runs StateMethod::executeStateMethod on the state at +0x220,
    // then Multi2D::animPlay on the layout at +0, view layer 0xE.
    // It always finishes with the button update at 0x025BE30C.
    // The button pointer array is at +0x0C. The current index is at +0x10.
    // The inclusive index range is +0x204 and +0x208.
    // The story menu uses 0 through 2: Continue, Quit, and Change Controller.
    // The button's name pointer is at button+0x54. Row 2 is Pa_PlayStyle_00.
    // The pad word is at +0x50. Down is bit 7, up is bit 6.
    // Plus is bit 11, Touch is bit 12, Decide is bit 13, and Back is bit 14.
    // A set bit 4 of the word at button+0x04 is a button the cursor may land on.
    // The open menu state is 0x10216DB4. Its execute at 0x025FDF98 reads +0x50.
    // A word of 3 at +0x1C enters 0x10216DD4. That state's enter starts the controller-window animation.
    // Plus or Back (mask 0x4800) changes to 0x10216DF4, which starts the same animation.
    // That state's execute waits for an animation flag, then enters 0x10216D74, which enters 0x10216D94.
    // 0x10216D94 is the controller window. Decide only sets +0xA91, and nothing opens the window from that byte.
    // Enter is Plus. A Settings confirm on Pa_PlayStyle_00 has to leave 0x10216DF4, 0x10216D74, or 0x10216D94.
    // The current state object is the pointer at +0x228. The pending state id is the pointer at +0x224.
    // Closing the overlay sets +0xA90 again. Those three states have to be gone before that, or the controller window opens.
    // The course object has already run 0x025FD500 before this function sees the frame.
    // Draw uses the bytes at +0x1E4, +0x1E6 or +0x1E5, and +0x8.
    // Address: 0x025F3834
    void execute();
};
