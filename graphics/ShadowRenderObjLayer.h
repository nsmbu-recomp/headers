#pragma once

#include <layer/aglRenderInfo.h>

// Depth shadows are a render-obj layer, not a per-frame clear.
// Course select builds the TV and DRC layers in CourseSelectLayerMgr::createLayers.
class ShadowRenderObjLayer
{
public:
    // Address: 0x024FF0E0
    ShadowRenderObjLayer();

    // Sets polygon offset and stencil state, then calls RenderObjRenderMgr::drawShadowOpa (0x024FC3F0).
    // Issues no GX2Clear*. The clear on the draw path belongs to ReflectionRenderObjLayer::render_.
    // Address: 0x024FF988
    void draw_(const agl::lyr::RenderInfo& render_info);
};
