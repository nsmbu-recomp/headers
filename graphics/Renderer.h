#pragma once

#include <graphics/RenderObjLayer.h>

#include <gfx/seadCamera.h>
#include <gfx/seadProjection.h>
#include <layer/aglLayer.h>
#include <layer/aglRenderer.h>
#include <math/seadBoundBox.h>

class   Angle;
class   AnimModel;
class   Model;
class   ModelFFL;
enum    UnitID;

class Renderer
{
    // createInstance()                             Address: 0x024FA650
    // deleteInstance()                             Address: Deleted
    // sInstance                                    Address: 0x101D2D88
    // SingletonDisposer_::~SingletonDisposer_()    Address: 0x024FAE28
    // SingletonDisposer_::sStaticDisposer          Address: 0x101D2D8C
    // SingletonDisposer_::vtbl                     Address: 0x100BDA98
    SEAD_SINGLETON_DISPOSER(Renderer)

public:
    static const s32 cDefaultRenderPass = -2;

    enum RenderPassType
    {
        cRenderPassType_Course = 0,     // AreaTask
        cRenderPassType_CourseSelect,   // CourseSelectTask, DarkCloudDemoScene, GameSetupScene, MultiPlayCourseSelectScene, ResultScene
        cRenderPassType_DemoScene,      // DemoTestScene
        cRenderPassType_Misc            // CourseTask, ChallengeResultScene, WithMiiPackSelectScene
    };

public:
    template <RenderPassType render_pass_type>
    class LayerSetter
    {
    public:
        LayerSetter(s32 layer_id)
        {
            Renderer::instance()->setLayer(agl::lyr::Renderer::instance()->getLayer<RenderObjLayerBase>(layer_id), render_pass_type);
        }

        LayerSetter(RenderObjLayerBase* p_layer)
        {
            Renderer::instance()->setLayer(p_layer, render_pass_type);
        }

        ~LayerSetter()
        {
            Renderer::instance()->resetLayer();
        }
    };

    template <s32 temp_layer_id, s32 post_layer_id, RenderPassType render_pass_type>
    class LayerSwitcher
    {
    public:
        LayerSwitcher()
        {
            setLayer_(temp_layer_id);
        }

        ~LayerSwitcher()
        {
            setLayer_(post_layer_id);
        }

    private:
        void setLayer_(s32 layer_id)
        {
            Renderer::instance()->resetLayer();
            Renderer::instance()->setLayer(agl::lyr::Renderer::instance()->getLayer(layer_id), render_pass_type);
        }
    };

public:
    // Address: 0x024FA5A0
    Renderer();
    // Address: 0x024FA6D0
    ~Renderer();

    // Address: 0x024FA748
    void setViewBoundBox(const sead::BoundBox2f& box);

    // Address: 0x024FA76C
    // Fills the course ortho from the renderer view box at Renderer+0x10 (min x, min y, max x, max y).
    // The call is OrthoProjection::setTBLR (0x02A06818) with (-min y, -max y, min x, max x).
    // setTBLR stores top, bottom, left, and right at object offsets 0x9C, 0xA0, 0xA4, and 0xA8.
    // Course-layer tile draws read that live ortho at RenderInfo+0x18.
    // 0x026919A4 and 0x0269325C are two of those draws.
    // The tile projection is copied into the display list at record time. A later change to the live ortho does not move the ground.
    // The recorded ground matrix matches OrthoProjectionSync mViewProj at +0x44 except element 5, the vertical scale, which is negated.
    // The tile draw negates top and bottom before OrthoProjection_syncViewProj (0x02A05A9C).
    void calcForAreaTask();

    // Address: 0x024FAA50
    void setLayer(agl::lyr::Layer* p_layer, RenderPassType render_pass_type);
    // Address: 0x024FAB4C
    void resetLayer();

    // Address: 0x024FAB58
    void drawModel(Model* p_model);
    // Address: 0x024FAC98
    void drawModel(const AnimModel* p_model);
    // Address: 0x024FACA0
    void drawModel(ModelFFL* p_model);

    // Address: 0x024FAD28
    void drawActorBgUnit(UnitID unit, const sead::Vector3f& pos, Angle angle, const sead::Vector3f& scale);
    // Address: 0x024FADD8
    void drawActorBgUnitLayer0(UnitID unit, const sead::Vector3f& pos, Angle angle, const sead::Vector3f& scale);

private:
    sead::BoundBox2f        mViewBoundBox;
    sead::OrthoProjection   mProjection3D;
    sead::OrthoCamera       mCamera3D;
    RenderObjLayerBase*     mpLayer;
    s32                     mDefaultOpaRenderPass;
    s32                     mDefaultXluRenderPass;
    sead::OrthoProjection   mProjectionFinalKoopa;
    sead::OrthoCamera       mCameraFinalKoopa;
};
static_assert(sizeof(Renderer) == 0x234);
