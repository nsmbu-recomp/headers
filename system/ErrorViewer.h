#pragma once

#include <basis/seadTypes.h>

class ErrorViewer
{
public:
    // Address: 0x029CBBB4
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
