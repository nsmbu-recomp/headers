#pragma once

#include <basis/seadTypes.h>

// Guessed name.
// The ring pointer is the word at this+0x4A8.
// A nested grow can observe that word as 0 until the outer grow publishes it.
class FrameAllocator
{
public:
    // Guessed name.
    // Grows the frame ring. r4 is 1 when the caller at 0x02ACD18C asks for a nested grow.
    // Address: 0x02ACD218
    void grow(u32 nested);
};
