#pragma once

#include <layout_sys/AnimLayout.h>

class SelectCursorMiniLayout : public AnimLayout<3>  // vtbl Address: 0x100CE654
{
public:
    // Address: 0x02645CCC
    void create();
};
static_assert(sizeof(SelectCursorMiniLayout) == 0xEC8);
