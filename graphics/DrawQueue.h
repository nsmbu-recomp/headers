#pragma once

#include <basis/seadTypes.h>

// Guessed name.
// Registered as a draw callback beside the Capture layer name.
// The object keeps model lists at +0x268, +0xE7C, +0x1A90, and +0x26A4.
class ModelDrawMgr
{
public:
    // Guessed name.
    // Locks the section at this+0x35D4. When the word at r4 is 0, runs the four list passes.
    // A node model pointer lives at node+0x28. A null pointer is not a model.
    // Address: 0x024D752C
    void buildQueues(const u32* flag);
};
