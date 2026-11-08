#pragma once

#include <utility/Angle3.h>

#include <common/aglShaderProgramArchive.h>
#include <heap/seadHeap.h>
#include <layer/aglRenderInfo.h>
#include <math/seadVector.h>

enum LayerID;
enum UnitID;

class BgRenderer
{
    SEAD_SINGLETON_DISPOSER(BgRenderer)

public:
    static void initializeShader(agl::ShaderProgramArchive* p_archive, sead::Heap* heap);

public:
    BgRenderer();
    ~BgRenderer();

    void drawActorBgUnit(LayerID layer, UnitID unit, const sead::Vector3f& pos, const Angle3& rot, const sead::Vector3f& scale);

    // Guessed names. Callers load this object from the word at 0x101EAFE8.
    // drawLayer1 binds the layer0_texture uniform next to the BgRenderer string.
    // Each draw reads the live ortho at RenderInfo+0x18.

    // Guessed name. Dispatcher 0x024B3CA0 when r5 is 0. RenderInfo is in r4.
    // Address: 0x026904D4
    void drawLayer0(const agl::lyr::RenderInfo& render_info);

    // Guessed name. Dispatcher 0x024B3FA0 when r5 is 0. RenderInfo is in r4.
    // Address: 0x026905C0
    void drawLayer0Second(const agl::lyr::RenderInfo& render_info);

    // Guessed name. Dispatcher 0x024B3CA0 when r5 is 1. Binds layer0_texture. RenderInfo is in r4.
    // Address: 0x02690680
    void drawLayer1(const agl::lyr::RenderInfo& render_info);

    // Guessed name. Dispatcher 0x024B3FA0 when r5 is 1. RenderInfo is in r4.
    // Address: 0x0269083C
    void drawLayer1Second(const agl::lyr::RenderInfo& render_info);

    // Guessed name. Called immediately after drawLayer1Second. RenderInfo is in r4.
    // Address: 0x02691690
    void drawLayer1SecondCont(const agl::lyr::RenderInfo& render_info);

    // Guessed name. Dispatcher 0x024B3CA0 when r5 is 2. RenderInfo is in r4.
    // Address: 0x0269179C
    void drawLayer2(const agl::lyr::RenderInfo& render_info);

    // Guessed name. Dispatcher 0x024B3FA0 when r5 is 2. RenderInfo is in r4.
    // Address: 0x026917E4
    void drawLayer2Second(const agl::lyr::RenderInfo& render_info);

    // Guessed name. Called immediately after drawLayer2Second. RenderInfo is in r4.
    // Address: 0x02691868
    void drawLayer2SecondCont(const agl::lyr::RenderInfo& render_info);

    // Guessed name. Dispatcher 0x024B3CA0 when r5 is 3. Branches to 0x0269018C. RenderInfo is in r4.
    // Address: 0x0269196C
    void drawLayer3(const agl::lyr::RenderInfo& render_info);

    // Guessed name. Dispatcher 0x024B3FA0 when r5 is 3. RenderInfo is in r4.
    // Address: 0x02691970
    void drawLayer3Second(const agl::lyr::RenderInfo& render_info);

    // Guessed name. Switch 0x024B40B4 case 0. RenderInfo is in r4.
    // Address: 0x026919A4
    void drawSwitch0(const agl::lyr::RenderInfo& render_info);

    // Guessed name. Switch 0x024B40B4 case 2. RenderInfo is in r4.
    // Address: 0x02691A8C
    void drawSwitch2(const agl::lyr::RenderInfo& render_info);

    // Guessed name. Dispatcher 0x024B3EB8 when r5 is 3. Binds reduce_gbuffer_texture and the label "Reduced G-Buffer".
    // RenderInfo is in r4.
    // Address: 0x02691B74
    void drawReducedGBuffer(const agl::lyr::RenderInfo& render_info);

    // Guessed name. Switch 0x024B40B4 case 3. RenderInfo is in r4.
    // Address: 0x02691DF0
    void drawSwitch3(const agl::lyr::RenderInfo& render_info);

    // Guessed name. Switch 0x024B40B4 case 10. RenderInfo is in r4.
    // Address: 0x02691EAC
    void drawSwitch10(const agl::lyr::RenderInfo& render_info);

    // Guessed name. Switch 0x024B40B4 case 15. RenderInfo is in r4.
    // Address: 0x0269206C
    void drawSwitch15(const agl::lyr::RenderInfo& render_info);

    // Guessed name. Dispatcher 0x024B3EB8 when r5 is 13. RenderInfo is in r4.
    // Address: 0x026920B0
    void drawStep13(const agl::lyr::RenderInfo& render_info);

    // Guessed name. Switch 0x024B40B4 case 13. RenderInfo is in r4.
    // Address: 0x02692194
    void drawSwitch13(const agl::lyr::RenderInfo& render_info);

    // Guessed name. Switch 0x024B40B4 case 14, before drawGround. RenderInfo is in r4.
    // Address: 0x0269222C
    void drawSwitch14(const agl::lyr::RenderInfo& render_info);

    // Guessed name. Dispatcher 0x024B3EB8 when r5 is 17. RenderInfo is in r4.
    // Address: 0x02692748
    void drawStep17(const agl::lyr::RenderInfo& render_info);

    // Guessed name. Switch 0x024B40B4 case 17. RenderInfo is in r4.
    // Address: 0x0269282C
    void drawSwitch17(const agl::lyr::RenderInfo& render_info);

    // Guessed name. Switch 0x024B40B4 case 18. RenderInfo is in r4.
    // Address: 0x026928C4
    void drawSwitch18(const agl::lyr::RenderInfo& render_info);

    // Guessed name. Ground and brick pass. Switch 0x024B40B4 case 14 passes layer 3 in r4 and RenderInfo in r5.
    // Address: 0x0269325C
    void drawGround(s32 layer, const agl::lyr::RenderInfo& render_info);
};
