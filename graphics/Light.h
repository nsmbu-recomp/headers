#pragma once

#include <gfx/seadColor.h>
#include <heap/seadDisposer.h>
#include <math/seadVector.h>

enum LightType;

class Light : public sead::IDisposer    // vtbl Address: 0x100BB350
{
public:
    // Address: 0x024E24BC
    Light();
    // Address: 0x024E2580
    virtual ~Light();

    // Address: 0x024E26BC
    bool update(
        LightType type,
        sead::Vector3f* p_position = nullptr,
        u32* = nullptr,
        f32* p_radius = nullptr,
        f32* = nullptr,
        sead::Color4f* p_color = nullptr,
        f32* = nullptr,
        f32* = nullptr
    );

private:
    bool            _10;
    void*           _14;
    sead::Vector3f  mPosition;
    u32             _24;
    f32             mRadius;
    f32             _2C;
    sead::Color4f   mColor;
    u32             _40;
    f32             _44;
};
static_assert(sizeof(Light) == 0x48);

// Stores p_position on the light entry and initializes the two embedded slot objects at 0x48 and 0x90.
// Called from Light::update when the registered entry pointer at offset 0x14 is non-null.
// Address: 0x024E2A0C
void sub_024E2A0C(void* p_entry, sead::Vector3f* p_position);
