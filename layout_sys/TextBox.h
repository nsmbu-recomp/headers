#pragma once

class TextBox  // vtbl Address: 0x100E45D8
{
public:
    // Address: 0x02681BFC
    // setTextBoxMessageFromTextID pulls strings from the game MSBT pipeline.
    // A custom string that is not a layout text has to hook this.
    void setMessageParam_(s32 param);

protected:
    u8 _00[0x1A4];
};
static_assert(sizeof(TextBox) == 0x1A4);
