#pragma once

class PauseGame
{
public:
    // Steps the in-level pause menu for one frame.
    // The singleton is the pointer at 0x101D830C.
    // A zero byte at +0x250 skips the state machine and the menu animation.
    // Otherwise this runs StateMethod::executeStateMethod on the state at +0x220,
    // then Multi2D::animPlay on the layout at +0, view layer 0xE.
    // It always finishes with the button update at 0x025BE30C.
    // The button pointer array is at +0x0C. The current index is at +0x10.
    // The inclusive index range is +0x204 and +0x208.
    // The story menu uses 0 through 2: Continue, Quit, and Change Controller.
    // When the pause Settings option is on, row 2 is Settings and its Decide must not enter that state.
    // The pad word is at +0x50. Down is bit 7, up is bit 6, Decide is bit 13.
    // A set bit 4 of the word at button+0x04 is a button the cursor may land on.
    // Decide plays the button click, then the idle state enters 0x10216608.
    // That state's enter is 0x025F3E9C. It starts the menu-out animation.
    // A Settings confirm must not enter that state. The menu stays open and the overlay opens instead.
    // Draw uses the bytes at +0x1E4, +0x1E6 or +0x1E5, and +0x8.
    // Address: 0x025F3834
    void execute();
};
