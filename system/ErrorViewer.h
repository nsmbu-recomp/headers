#pragma once

#include <basis/seadTypes.h>

class ErrorViewer
{
public:
    // Address: 0x029CBBB4 in USA 1.3.0. Europe 1.3.0 compiles the same 580-byte function at 0x029CBC58.
    // Both versions show the error viewer.
    // USA writes 1 to the kind field at offset 12 of the message struct it builds on the stack.
    // Europe writes 2 to that field. The field is not an ErrorViewer member.
    // Display mode comes from *(*(0x101D7D68) + 0x10).
    // USA: display mode 1 selects kind 2, display mode 2 selects kind 5, and any other mode selects kind 1.
    // Europe display modes 1 through 7 load a kind byte from 0x10189E27 indexed by the mode.
    // Those bytes are 2, 3, 4, 5, 8, 9, and 10. A mode outside that range selects kind 1.
    // USA has no such table at 0x10189E27.
    s32 show(void* message, u8 displayParam);

private:
    u32                     _00[0x5C / sizeof(u32)];
    void*                   mpLink;
    u32                     _60[(0x154 - 0x60) / sizeof(u32)];
    void*                   mpLayout;
    u8                      mIsShowing;
    u8                      _159[3];
    u32                     mMessageState;
    u8                      mDisplayParam;
    u8                      mResultFlag;
    u8                      _162[2];
    s32                     mStoredValue;
    u32                     _168[(0x550 - 0x168) / sizeof(u32)];
    u8                      mLayoutScratch[0x10];
};
