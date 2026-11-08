#pragma once

#include <basis/seadTypes.h>

namespace sead {

class OrthoProjection
{
public:
    // Stores top, bottom, left, and right at +0x9C, +0xA0, +0xA4, and +0xA8.
    // Address: 0x02A06818
    void setTBLR(f32 top, f32 bottom, f32 left, f32 right);
};

class PerspectiveProjection
{
public:
    // near, far, field of view in radians, then aspect.
    // Address: 0x02A061AC
    PerspectiveProjection(f32 near, f32 far, f32 fov, f32 aspect);

    // Same argument order. Field of view is stored at +156. Aspect is stored at +172.
    // Address: 0x02A062EC
    void set(f32 near, f32 far, f32 fov, f32 aspect);
};

}
