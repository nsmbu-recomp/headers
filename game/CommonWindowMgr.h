#pragma once

#include <layout/CommonWindow.h>

#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <layer/aglRenderInfo.h>

class CommonWindowMgr
{
    // createInstance()                             Address: 0x024BC444
    // deleteInstance()                             Address: Deleted
    // sInstance                                    Address: 0x101D15E8
    // SingletonDisposer_::~SingletonDisposer_()    Address: 0x024BC874
    // SingletonDisposer_::sStaticDisposer          Address: 0x101D15EC
    // SingletonDisposer_::vtbl                     Address: 0x100B7014
    SEAD_SINGLETON_DISPOSER(CommonWindowMgr)

public:
    enum PadTrigStatus
    {
        cStatus_Decide = 0,
        cStatus_Back,
        cStatus_Disabled,
        cStatus_Dpad,       // Maybe???
        cStatus_Idle
    };

public:
    // Address: 0x024BC3C4
    CommonWindowMgr();

    // Address: 0x024BC4C4
    // Builds the embedded CommonWindow once: CommonWindow::create, which runs createLayoutObj, readResource, build, pane registration, and PaCursor setup on the layout at +0x24.
    void create();

    // Address: 0x024BC540
    // Runs CommonWindow::execute (state machine and animPlay on layer 0xE when visible).
    void execute();

    // Address: 0x024BC590
    // TV draw. GamePad and system DRC are drawDRC and drawDRC_System. A GamePad-only flow needs the DRC path as well.
    void draw(const agl::lyr::RenderInfo& render_info) const;

    // Address: 0x024BC5A4
    void drawDRC(const agl::lyr::RenderInfo& render_info) const;        // Only draws if mCommonWindow.mIsSystemDRC == false
    // Address: 0x024BC5C4
    void drawDRC_System(const agl::lyr::RenderInfo& render_info) const; // Only draws if mCommonWindow.mIsSystemDRC == true

    // Pause is not a separate function. Callers set this on the singleton:
    // mRequestOpen, mType = cType_WinText_Pause, and the message type.
    // Message copy can differ through msg_text_type while the window kind stays pause.
    // PaCursor and the controller slots on this mgr consume input while the window is open.
    void open(
        CommonWindow::Type type,
        SysController::Id controller_id = SysController::cId_CafeDRC_SinglePlayer,
        CommonWindow::Type msg_text_type = CommonWindow::cDefaultMsgTextType
    )
    {
        mCommonWindow.mRequestOpen = true;
        mCommonWindow.mType = type;
        mCommonWindow.mMsgTextType = msg_text_type;
        mCommonWindow.mIsSystemDRC = false;
        mCommonWindow.cursorResetDecideTrig();

        mIsActive = true;
        mCurrentControllerId = controller_id;
    }

    void setHideBackButton(bool hide)
    {
        mCommonWindow.mHideBackButton = hide;
    }

    void setSystemDRC(bool enable)
    {
        mCommonWindow.mIsSystemDRC = enable;
    }

    void close()
    {
        mCommonWindow.mRequestClose = true;
    }

    bool isOpen() const
    {
        return mCommonWindow.mRequestOpen;
    }

    bool isVisible() const
    {
        return mCommonWindow.mIsVisible;
    }

    bool isTransitionAnime() const
    {
        return mCommonWindow.mIsTransitionAnime;
    }

    bool isFadeOut() const
    {
        return mCommonWindow.mIsFadeOut;
    }

    // Address: 0x024BC5E4
    // Delegates to CommonWindow::processPadTrigTwoButtons.
    // That installs a handler from lookupPadTrigFuncTwoButtons_ (indexed by CommonWindow::Type at +0x1AA0) into +0x1128, then drives PaCursor and FStateMgr.
    PadTrigStatus processPadTrig_TwoButtons(bool enable_back_button);   // i.e., Window has two UI buttons
    // Address: 0x024BC7D4
    // Same path as processPadTrig_TwoButtons, for the one-button lookup.
    PadTrigStatus processPadTrig_OneButton();                           // i.e., Window has one UI button

    bool cursorIsOnLeftButton() const
    {
        return mCommonWindow.cursorIsOnLeftButton();
    }

    bool cursorIsOnRightButton() const
    {
        return mCommonWindow.cursorIsOnRightButton();
    }

    void cursorTriggerDecide()
    {
        mCommonWindow.cursorTriggerDecide();
    }

    bool cursorIsNoPadInput() const
    {
        return mCommonWindow.cursorIsNoPadInput();
    }

    void setFreezePostDecide(bool freeze)
    {
        mCommonWindow.mFreezePostDecide = freeze;
    }

    bool isDoneOutQuickSaveAnime() const
    {
        return mCommonWindow.mIsDoneOutQuickSaveAnime;
    }

private:
    CommonWindow                mCommonWindow;
    sead::SafeArray<
        SysControllerWrapper,
        SysController::cId_Max
    >                           mControllers;
    SysController::Id           mCurrentControllerId;
    bool                        mIsActive;
};
static_assert(sizeof(CommonWindowMgr) == 0x22B8);
