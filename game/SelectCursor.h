#pragma once

#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>

#include <layout/SelectCursorLayout.h>
#include <layout/SelectCursorMiniLayout.h>

#include <layer/aglRenderInfo.h>

class SelectCursor
{
    // createInstance()                             Address: 0x024C635C
    // deleteInstance()                             Address: Deleted
    // sInstance                                    Address: 0x101D17A8
    // SingletonDisposer_::~SingletonDisposer_()    Address: 0x024C6930
    // SingletonDisposer_::sStaticDisposer          Address: 0x101D17AC
    // SingletonDisposer_::vtbl                     Address: 0x100B8600
    SEAD_SINGLETON_DISPOSER(SelectCursor)

public:
    // Address: 0x024C6298
    SelectCursor();

    // Address: 0x024C63E0
    // File-select cursor chrome. sInstance is 0x101D17A8. The typed layouts are SelectCursorLayout.
    void create();

    // Address: 0x024C6500
    void execute();

    // r4 is the button the cursor follows. r5 is the cursor type. Type 0x18 returns.
    // The layout stores that button at +0xEA0 and enables itself.
    // Address: 0x024C6744
    void set(void* button, s32 type, s32);

    // Hides one cursor layout slot. type is a SelectCursorType index.
    // Types 0x12 through 0x15, and type 9, use mMiniLayout. Other types use mLayout.
    // Type 2 is the pause-menu yellow cursor, in mLayout. This clears only that slot.
    // The draw byte at +0x2C5F4 is not touched.
    // Address: 0x024C67B4
    void hide(s32 type);

    // Address: 0x024C65A0
    // A clear byte at +0x2C5F4 returns before any cursor is drawn.
    void draw(const agl::lyr::RenderInfo& render_info) const;

    // Address: 0x024C6680
    void drawDRC(const agl::lyr::RenderInfo& render_info) const;

private:
    u8                                          _10[0x10];
    sead::SafeArray<SelectCursorLayout, 24>     mLayout;
    sead::SafeArray<SelectCursorMiniLayout, 24> mMiniLayout;
    u32                                         _2c5f0;
    u8                                          _2c5f4;
};
static_assert(sizeof(SelectCursor) == 0x2C5F8);
