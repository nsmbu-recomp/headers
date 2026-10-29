#pragma once

#include <layout_sys/AnimLayout.h>

class SelectCursorLayout : public AnimLayout<3>  // vtbl Address: 0x100CE568
{
public:
    // Address: 0x026454E4
    void create();

    // create() stores getRootPane() at +0xEA4 and sets +0xEBF / +0xEC3 for player slots 0x16..0x17.

protected:
    u32                             _sizeTail;
};
static_assert(sizeof(SelectCursorLayout) == 0xECC);
