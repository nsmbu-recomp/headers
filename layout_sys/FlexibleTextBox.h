#pragma once

#include <layout_sys/TextBox.h>

class FlexibleTextBox : public TextBox
{
protected:
    u8 _1A4[0x1C8 - 0x1A4];
};
static_assert(sizeof(FlexibleTextBox) == 0x1C8);
