#pragma once

#include <actor/ActorCullRange.h>

#include <math/seadBoundBox.h>

class ActorCullUtil
{
public:
    // Address: 0x02008838
    // Tests the zoom box at BgScrollMgr+0x48.
    static bool screenCullCheck(const sead::BoundBox2f& range, const ActorCullRange& cull_range);
    // Address: 0x02008918
    // Tests the screen box at BgScrollMgr+0x28. Actor::drawCullCheck_ uses this box.
    static bool screenCullCheck(const sead::BoundBox2f& range);
    // Address: 0x0200897C
    static bool areaCullCheck(const sead::BoundBox2f& range, u8 area_no);
};
