#pragma once

#include <basis/seadTypes.h>

namespace nw { namespace lyt {

class AnimTransform
{
public:
    // Guessed name.
    // Stores the resource at this+8 and reads the animation count at resource+0xC.
    // r4 is the pai1 block. r5 and r6 are the other two arguments. r6 sizes one allocation.
    // Five animation tables share this function.
    // The world-map Settings button takes its open and close curves from the neighboring buttons here.
    // Address: 0x02AB702C
    void SetResource(const void* resource, void* accessor, u32 index);
};

} }
