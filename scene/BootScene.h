#pragma once

#include <framework/seadCalculateTask.h>
#include <framework/seadTaskMgr.h>
#include <state/StateMethod.h>

class Scene;

class BootScene : public sead::CalculateTask   // vtbl Address: 0x101759D8
{
public:
    // Address: 0x0297AC48
    BootScene(const sead::TaskConstructArg& arg);

    // Address: 0x0297AF6C
    void calc();

private:
    // Address: 0x0297B068
    void setExitLatchFromTask();

    // Address: 0x0297B0A0
    bool requestFlowScene();

    // Address: 0x0297B130
    void resetExitFrameCount();

    // Address: 0x0297B13C
    void executeExitWaitState();

    // Address: 0x0297B17C
    void setExitReady();

    // Address: 0x0297B188
    void executeExitReadyState();

    // Address: 0x0297B1A4
    void tryConsumeExitLatch();

    u8 mStateFactoryEmbed[0xD8 - 0xC8];
    StateMethod mStateMethod;
    u8 _e8[0x168 - 0xE8];
    u8 mUi[0x102C - 0x168];
    u8 mHoldExitCount;
    u8 mExitReady;
    u8 _102e[0x1034 - 0x102E];
    u32 mExitFrameCount;
    u8 mExitLatch;
    u8 _1039[0x103C - 0x1039];
};
static_assert(sizeof(BootScene) == 0x103C);

// Address: 0x0297B1F0
void registerBootExitStates();

// Address: 0x02994494
u32 sceneHasPendingNext(Scene* scene);

// Address: 0x02A00D98
void bootSceneNotifyTaskMgr(sead::TaskMgr* mgr);

// Address: 0x0253543C
void calculateBootSceneUi(void* ui);

// Address: 0x02AFA52C
void linkStateRegistration(void* link_tag);

// Address: 0x0297B5EC
void bootExitStateFinalizePrimary(BootScene* scene);

// Address: 0x0297B5F0
void bootExitStateFinalizeHandoff(BootScene* scene);

// Address: 0x0297B5F4
void bootExitStateEnterConsume(BootScene* scene);

// Address: 0x0297B5F8
void bootExitStateFinalizeConsume(BootScene* scene);

// Address: 0x0202930C
extern template
sead::TaskBase* sead::TTaskFactory<BootScene>(const sead::TaskConstructArg& arg);
