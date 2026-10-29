#pragma once

#include <layout_sys/AnimLayout.h>

#include <math/seadVector.h>
#include <state/StateMethod.h>

class PlayerCourseHud
{
public:
    // Address: 0x0252F900
    void drawStockItemList();

protected:
    // Address: 0x0252F598
    void prepareStockItemList_();

    // Address: 0x0252F884
    void syncItemListAnims_();

protected:
    u8                              _0000[0x8C4];
    u8                              mSpinIcon[0x910 - 0x8C4];
    u8                              mStockItemList[0x17F0 - 0x910];
    StateMethod                     mStateMethod;
    u8                              _1800[0x1804 - 0x1800];
    AnimLayout<2>                   mItemListLayout;
    u8                              _afterItemList[0x6151 - (0x1804 + sizeof(AnimLayout<2>))];
    u8                              mDrawSpinIcon;
    u8                              _6152[0x67AC - 0x6152];
    u32                             _67AC;
    u32                             _67B0;
    u32                             _67B4;
    u32                             _67B8;
    u32                             _68B8;
    sead::Vector2f                  mStockItemPos;
    u8                              _68C4[0x696B - 0x68C4];
    u8                              mStockItemDrawFlag;
    u8                              mPreparedDrawFlag;
};
static_assert(offsetof(PlayerCourseHud, mStateMethod) == 0x17F0);
static_assert(offsetof(PlayerCourseHud, mItemListLayout) == 0x1804);
static_assert(offsetof(PlayerCourseHud, mStockItemDrawFlag) == 0x696B);
static_assert(sizeof(PlayerCourseHud) == 0x696D);
