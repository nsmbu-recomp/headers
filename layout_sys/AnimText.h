#pragma once

class AnimText
{
public:
    // Address: 0x02675984
    AnimText();

protected:
    u8 _00[0xB0];
};
static_assert(sizeof(AnimText) == 0xB0);
