#pragma once

#include <utility/Direction.h>

#include <heap/seadDisposer.h>
#include <math/seadBoundBox.h>

class BgScrollMgr;

// This is actually in a different file
class ScrollEffectMgr
{
public:
    ScrollEffectMgr(BgScrollMgr* scroll_mgr);

public:
    u32 _0[0x3c / sizeof(u32)];
    struct // This should be a separate class
    {
        u32 _0;
        f32 _4;
        f32 _8;
        u32 _c;
        f32 _10;
        f32 _14;
    } _3c;
};
static_assert(sizeof(ScrollEffectMgr) == 0x54);

enum ZoomType
{
    cZoomType_Normal = 0,
    cZoomType_TrackY,
    cZoomType_ExpandY,
    cZoomType_Static,
    cZoomType_Static_TrackY,
    cZoomType_5,
    cZoomType_TrackX,
    cZoomType_ExpandX
};
static_assert(sizeof(ZoomType) == 4);

class ZoomHioData
{
public:
    // Address: 0x029B0EBC
    f32 getZoomTargetMin_Common(bool) const;
    // Address: 0x029B0FF8
    f32 getZoomTargetMid_Common(bool) const;
    // Address: 0x029B113C
    f32 getZoomTargetMax_Common(bool) const;

    // Address: 0x029B1288
    f32 getZoomSpreadLine(bool) const;
    // Address: 0x029B13D8
    f32 getZoomSpreadLine2(bool) const;
    // Address: 0x029B1528
    f32 getZoomShrinkLine2(bool) const;
    // Address: 0x029B1678
    f32 getZoomShrinkLine(bool) const;

private:
    ZoomType    mZoomType;
    u8          mZoomID;
};
static_assert(sizeof(ZoomHioData) == 8);

class ZoomHio
{
public:
    // Address: 0x029B00D4
    ZoomHioData* getZoomHioData() const;
};

class TrackingMgr : public ZoomHio
{
public:
    // Address: 0x029AEB28
    f32 adjustZoomTarget(f32 zoom) const;

    f32 getZoomTargetMin(bool param_1 = false) const
    {
        return adjustZoomTarget(getZoomHioData()->getZoomTargetMin_Common(param_1));
    }

    f32 getZoomTargetMid(bool param_1 = false) const
    {
        return adjustZoomTarget(getZoomHioData()->getZoomTargetMid_Common(param_1));
    }

    f32 getZoomTargetMax(bool param_1 = false) const
    {
        return adjustZoomTarget(getZoomHioData()->getZoomTargetMax_Common(param_1));
    }

    f32 getZoomSpreadLine(bool param_1 = false) const
    {
        return getZoomHioData()->getZoomSpreadLine(param_1);
    }

    f32 getZoomSpreadLine2(bool param_1 = false) const
    {
        return getZoomHioData()->getZoomSpreadLine2(param_1);
    }

    f32 getZoomShrinkLine2(bool param_1 = false) const
    {
        return getZoomHioData()->getZoomShrinkLine2(param_1);
    }

    f32 getZoomShrinkLine(bool param_1 = false) const
    {
        return getZoomHioData()->getZoomShrinkLine(param_1);
    }
};

// sInstance is 0x101E7C54. The screen update is 0x029A6170. See getScreenRect.
class BgScrollMgr
{
    SEAD_SINGLETON_DISPOSER(BgScrollMgr)

public:
    BgScrollMgr();

    f32 getZoom() const { return mZoom; }

    const sead::BoundBox2f& getScrollBound() const { return mScroll; }
    // The screen box is written by 0x029A6170, which also copies it into the scalar window.
    // Left is +0x70, center X is +0x74, and right is +0x78.
    // The box is +0x28 (min X), +0x2C (min Y), +0x30 (max X), and +0x34 (max Y).
    // ActorCullUtil::screenCullCheck tests this box. The padded check at 0x02008838 tests the zoom box at +0x48.
    // Actor::drawCullCheck_ uses this box, so a 16:9 box hides actors the wide camera can already see.
    // The previous-frame box is +0x38. The fixed-size box is +0x58.
    // Background edges are +0x88 and +0x90. The previous background box is +0x98.
    // The same update can run again after it rewrites the screen box. A box already past 16:9 stays as it is.
    // The first of those two updates leaves the scalar window at 16:9.
    // The rewrite then builds the game's camera, and the second update widens that camera.
    // Title parade and other screen-follow placement read the scalar window, so a wider left and right slide that parade toward the new right edge.
    // A course widens the screen box, the zoom box, the scalar window, and the background box.
    // The widen pivots on the average X of players inside that 16:9 screen box. Each player's fraction of the width stays the same as 16:9.
    // The scalar center X becomes the midpoint of the widened left and right.
    // With no player inside the box, the pivot stays the old center.
    // The title course (CourseInfo::isTitle) does not widen the screen box, so the parade stays centered.
    // Its background box still widens around its own center. Background parts spawn from those edges on the title course too.
    const sead::BoundBox2f& getScreenRect() const { return mScreen; }
    const sead::BoundBox2f& getScreenRectPrev() const { return mScreenPrev; }
    const sead::BoundBox2f& getScreenRectDefault() const { return mScreenDefault; }

    f32 getScreenWidth() const { return mScreenWidth; }
    f32 getScreenHeight() const { return mScreenHeight; }
    f32 getScreenLeft() const { return mScreenLeft; }
    f32 getScreenCenterX() const { return mScreenCenterX; }
    f32 getScreenRight() const { return mScreenRight; }
    f32 getScreenTop() const { return mScreenTop; }
    f32 getScreenCenterY() const { return mScreenCenterY; }
    f32 getScreenBottom() const { return mScreenBottom; }

    ScrollEffectMgr& getScrollEffectMgr() { return mScrollEffectMgr; }
    const ScrollEffectMgr& getScrollEffectMgr() const { return mScrollEffectMgr; }

    // Address: 0x029A6400
    DirType getAreaScrollDir() const;

    // Address: 0x029A6D40
    f32 getBgCenterYPos() const;

    // Address: 0x029A6DC4
    bool isScrollMeterEnable() const;

    // Address: 0x029A6DE0
    ZoomType getZoomType() const;

    // Address: 0x029A6E24
    DirType getAreaScrollDirSub() const;

    // Address: 0x029A6E40
    void postDemoIn();

private:
    f32                 mZoom;
    f32                 mZoomPrev;
    sead::BoundBox2f    mScroll;
    sead::BoundBox2f    mScreen;
    sead::BoundBox2f    mScreenPrev;
    sead::BoundBox2f    mScreenZoom;        // Same center as mScreen, but size is determined by mZoom
    sead::BoundBox2f    mScreenDefault;     // Same center as mScreen, but size is (796.44, 448)
    f32                 mScreenWidth;       // In world space
    f32                 mScreenHeight;      // ^^^
    f32                 mScreenLeft;        // ^^^
    f32                 mScreenCenterX;     // ^^^
    f32                 mScreenRight;       // ^^^
    f32                 mScreenTop;         // ^^^
    f32                 mScreenCenterY;     // ^^^
    f32                 mScreenBottom;      // ^^^
    sead::BoundBox2f    mScreenBg;          // Same as mScreen, but Y is inverted
    sead::BoundBox2f    mScreenBgPrev;
    void*               mScrollInfo;
    void*               mMaxStopMgr;
    void*               mZoomAreaMgr;
    void*               mKyokaiVelMgr;
    TrackingMgr*        mTrackingMgr;
    void*               _bc;
    void*               _c0;
    void*               mAutoScrollMgr;
    void*               mConfigMgr;
    u32                 mScrollLimitInfo[0x2c / sizeof(u32)];
    ScrollEffectMgr     mScrollEffectMgr;
};
static_assert(sizeof(BgScrollMgr) == 0x14C);
