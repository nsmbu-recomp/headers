#pragma once

#include <graphics/RenderObjRenderMgr.h>

#include <common/aglRenderBuffer.h>

#include <layer/aglRenderInfo.h>

class ReflectionRenderObjLayer
{
public:
    // Address: 0x024F9C04, ending 0x024FA280.
    // Stored as a delegate at 0x024F9860 by the ctor 0x024F9800, so it is reached only through the layer render step.
    // 0x024F9E24 is the cRenderStep_Opa arm, not a function entry.
    // That arm clears this layer's own render buffer at 0x024FA07C with agl::RenderBuffer::clear (0x02A1E644):
    // target index 0, flags 3 (colour + depth), colour (0, 0, 1, 0), depth 1.0f, stencil 0.
    // That clear belongs to the reflection layer. The depth-shadow layer does not clear.
    void render_(const agl::lyr::RenderInfo& render_info);

private:
    u8                  _000[0x420];
    RenderObjRenderMgr* mpRenderMgr;            // +0x420
    s32                 mViewIndex;             // +0x424
    u8                  _428[0x004];
    void*               mpCameraProjection;     // +0x42C
    u8                  _430[0x048];
    void*               mpColorTarget;          // +0x478
    void*               mpDepthTarget;          // +0x47C
    u8                  _480[0x154];
    u8                  _5D4[0x160];
    agl::RenderBuffer   mRenderBuffer;          // +0x734
    u8                  _784[0x0E8];
    u8                  _86C[0x0B8];
    u8                  _924[0x0C0];
    f32                 mProjectionScale;       // +0x9E4
    u8                  _9E8[0x014];
    bool                _9FC;                   // +0x9FC
};
