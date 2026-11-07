#pragma once

#include <basis/seadTypes.h>

namespace sead { class Heap; }

class CourseSelectLayerMgr
{
public:
    // sInstance                                    Address: 0x101E8A2C
    static CourseSelectLayerMgr* instance()
    {
        return sInstance;
    }

    // Address: 0x021EE9E4
    // Creates "DepthShadow_DRC" (0x10047098) with layer id 0x17.
    // The factory 0x021EEFF8 allocates 0x1154 bytes and runs the ShadowRenderObjLayer ctor 0x024FF0E0.
    // The TV "DepthShadow" layer is also created here: layer id 5 at 0x021EEAD8, with the "CourseSelect" render mgr (0x100470D8) from 0x021EEA38.
    // A second TV "DepthShadow" string at 0x101768C0 is created with layer id 5 at 0x02980F44, in the game layer setup that starts at 0x02980E60.
    // That address is materialised as lis + addic. An addi-only sweep misses it.
    // "Shadow Map" (0x101A94AC), "shadow_map_depth" (0x101A94B8), and "vsm" (0x101A94D0) are agl render-target setup names, not these passes.
    // They are used at 0x02A4DF84, 0x02A4E018, and 0x02A4E3B0 inside the agl class whose ctor is 0x02A4DC00 (size 0xB38, vtable 0x101A94E0, dtor 0x02A4DD70).
    // That class passes name pairs to 0x02A5069C, which is a blr, so creation is 0x02A528D0 through *(0x101F8A50).
    // "static_depth_shadow" (0x101A658C) is an agl::detail::ShaderHolder sShaders[] entry at rodata 0x101A6000.
    static void createLayers(sead::Heap* heap);

private:
    static CourseSelectLayerMgr* sInstance;
};
