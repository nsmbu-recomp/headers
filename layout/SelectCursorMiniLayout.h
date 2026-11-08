#pragma once

#include <layout_sys/AnimLayout.h>

class SelectCursorMiniLayout : public AnimLayout<3>  // vtbl Address: 0x100CE654
{
public:
    // Address: 0x02645CCC
    void create();

    // Address: 0x02645CB4
    void hideIfEnabled();

    // Address: 0x02645FC0
    void disable();
};
static_assert(sizeof(SelectCursorMiniLayout) == 0xEC8);
