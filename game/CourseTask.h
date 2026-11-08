#pragma once

#include <game/FieldGame.h>

#include <framework/seadCalculateTask.h>
#include <framework/seadTaskMgr.h>

class CourseInfo;
class CourseTask;
class GamesceneBase;
class InputMgr;

namespace sead {
class Heap;
}

// Address: 0x024D29A4
void CourseInfo_applyNextWorldCourseToNow(CourseInfo* course_info);

// Address: 0x024D3888
bool CourseInfo_isCourseNo0x39(CourseInfo* course_info);

// Address: 0x024D38B4
bool CourseInfo_isSpecialCourseNo(CourseInfo* course_info);

// Address: 0x024D29B8
void CourseInfo_commitNextFromCourseData(CourseInfo* course_info);

// Address: 0x024CD56C
u8 PicturePaneMgr_lookupGlyph(void* pane_mgr, u8 world_no, u8 course_no);

// Address: 0x0250CDBC
void InputMgr_applySaveEntry_(InputMgr* mgr, void* save_entry, s32 mode, s32 unused);

// Address: 0x029CB318
void CommentMgr_onCourseSetup(class CommentMgr* mgr);

// Address: 0x024B4884
void CourseTask_allocCourseHeap(s32 heap_id);

// Address: 0x020298DC
void CourseSetupStack_pushSentinels();

// Address: 0x029C8508
void MainGame_setCourseBanner(u8 world_no, u8 course_no);

// Address: 0x024CEA10
s32 SaveData_getPlayMode();

// Address: 0x024CE594
void ChallengeMgr_setCourseFlag();

// Address: 0x024CE690
bool ChallengeMgr_isActive();

// Address: 0x024BD7C8
s32 CourseTask_selectEntryCharacter(CourseTask* task);

// Address: 0x024BD4F8
void CourseTask_bindCourseResNode(void* node);

// Address: 0x0269A2B4
void CourseResPackNameBuilder_build(u8 world_no, u8 course_no);

// Address: 0x0269A1B0
void CourseResPackNameBuilder_teardown();

// Address: 0x0269A244
void CourseData_releaseFileRef();

// Address: 0x0269A2DC
void* CourseData_getFile(s32 index);

// Address: 0x02A0A7AC
GamesceneBase* GamesceneFactory_create(void* out_pair, const void* type_info, s32 heap_id, s32 a, s32 b);

// Address: unknown (0x02A0D584 was mis-tagged; that PC is HeapMgr::setCurrentHeap)
// sead::HeapMgr::setCurrentHeap is 0x02A0D584. getCurrentHeap is 0x02A0D554.
// Both load a Cafe thread-specific slot id from *(0x101E80A0)+0x20, then call OSGetThreadSpecific.
// The sead Thread object keeps the current heap at +0x6C.
// Many sInstance pointers sit in MEM2 between RPX sections (about 0x101CB7C8-0x101E93BF), including that TLS root.
// The range is inside .data (0x101C30C0-0x101E93B4) except the last 0xB bytes, and .data is PROGBITS.
// A section reload rewrites it. Cold boot is fine because anonymous guest memory starts zeroed.
// A later setCurrentHeap on a thread whose OSThread TLS was wiped faults at guest 0x6C.
s32 GamesceneFactory_release(void* object);

// Address: 0x02994044
void AreaTask_createFromCourseTask(CourseTask* task);

// Address: 0x0202AEDC
void CourseTask_onSetupComplete();

// Address: 0x02893DE4
void TouchDrcMgr_createInstance();

// Address: 0x0219DAF4
void ActorCollisionCheckMgr_createInstance();

// Address: 0x020043F0
void f_020043F0();

// Address: 0x026CA474
void ActorCoinMgr_createInstance();

// Address: 0x0270B65C
void BlockMgr_createInstance();

// Address: 0x02027A0C
void ScoreMgr_createInstance();

// Address: 0x02192460
void ActorBgCollisionMgr_createInstance();

// Address: 0x021B1014
void UnitBgCollisionHolder_createInstance();

// Address: 0x022C9288
void f_022C9288();

// Address: 0x024C1838
void f_024C1838();

// Address: 0x0250A698
void f_0250A698();

// Address: 0x02816A7C
void f_02816A7C();

// Address: 0x02891458
void f_02891458();

// Address: 0x028914EC
void f_028914EC();

// Address: 0x024D967C
void f_024D967C();

// Address: 0x024D9744
void f_024D9744();

// Address: 0x028D3A60
void f_028D3A60();

// Address: 0x028D3B40
void f_028D3B40();

// Address: 0x024ED434
void f_024ED434();

// Address: 0x024EDAA0
void f_024EDAA0();

// Address: 0x024C18B8
void f_024C18B8();

// Address: 0x0269B0D8
void f_0269B0D8();

// Address: 0x0268E0EC
void f_0268E0EC();

// Address: 0x0268F428
void f_0268F428();

// Address: 0x0268BE54
void f_0268BE54();

// Address: 0x02916AF0
void f_02916AF0();

// Address: 0x02742D2C
void sub_02742D2C(u32 arg = 0);

// Address: 0x0269BB7C
void f_0269BB7C();

// Address: 0x0202ADC4
void f_0202ADC4();

// Address: 0x0200A738
void ActorResLoader_load(s32 a, s32 b);

// Address: 0x022A6048
void f_022A6048(CourseTask* task, u32 entry_index);

// Address: 0x026CA03C
void f_026CA03C();

// Address: 0x0291713C
void f_0291713C();

// Address: 0x02742F9C
void f_02742F9C();

// Address: 0x0269BC94
void f_0269BC94();

// Address: 0x0268E888
void f_0268E888();

// Address: 0x0268F7F0
void f_0268F7F0();

// Address: 0x0250A840
void f_0250A840();

// Address: 0x02657CA4
void f_02657CA4();

// Address: 0x025CE934
void f_025CE934();

// Address: 0x0252E6C4
void f_0252E6C4();

// Address: 0x0258B084
void f_0258B084();

// Address: 0x0253B5CC
void f_0253B5CC();

// Address: 0x02532D14
void f_02532D14();

// Address: 0x02666DA8
void f_02666DA8();

// Address: 0x0258C1F0
void f_0258C1F0();

// Address: 0x02650F7C
void f_02650F7C();

// Address: 0x02650344
void f_02650344();

// Address: 0x0264E25C
void f_0264E25C();

// Address: 0x02537290
void f_02537290();

// Address: 0x025396C4
void f_025396C4();

// Address: 0x024E4318
void LightMapMgr_initialize();

// Address: 0x02551B04
void f_02551B04();

// Address: 0x025F4B24
void f_025F4B24();

// Address: 0x025BE710
void f_025BE710();

// Address: 0x02646F58
void f_02646F58();

// Address: 0x02627FF4
void f_02627FF4();

// Address: 0x026287BC
void f_026287BC();

// Address: 0x02614CD0
void f_02614CD0();

// Address: 0x02534138
void f_02534138();

// Address: 0x02667C9C
void f_02667C9C();

// Address: 0x026533B0
void f_026533B0();

// Address: 0x02657278
void f_02657278();

// Address: 0x025846D4
void f_025846D4();

// Address: 0x025F281C
void f_025F281C();

// Address: 0x024CC8E8
void f_024CC8E8();

// Address: 0x024BC4C4
void f_024BC4C4();

// Address: 0x025FBCF0
void f_025FBCF0();

// Address: 0x025F2F50
void f_025F2F50();

// Address: 0x024B3544
void f_024B3544();

// Address: 0x0255B524
void f_0255B524();

// Address: 0x026444A8
void f_026444A8();

// Address: 0x026661D8
void f_026661D8();

// Address: 0x02422BA0
void TottenMgr_createInstance();

// Address: 0x024230A8
void f_024230A8();

class CourseTask : public sead::CalculateTask   // vtbl Address: 0x100B734C
{
    // setInstance_()                               Address: 0x024BCA80
    // deleteInstance()                             Address: Deleted
    // sInstance                                    Address: 0x101D15F0
    // SingletonDisposer_::~SingletonDisposer_()    Address: 0x024BC924
    SEAD_TASK_SINGLETON_DISPOSER(CourseTask)

public:
    static FieldGameData& getActiveGameData()
    { 
        return
            (instance() != nullptr)
                ? *instance()->getGameData()
                : FieldGame::instance()->getGameData();
    }

public:
    // Address: 0x024BCAA0
    CourseTask(const sead::TaskConstructArg& arg);
    // Address: 0x024BC950
    virtual ~CourseTask();

    // Runs before the area task loads the course pack.
    // FieldGameData, through CourseTask+0x124 / mGameData:
    // 1. memcpy from FieldGame::getGameData(), the singleton filled by save, load, and map logic.
    // 2. resetEntriesUnk30 and setupNabbitEntry.
    // 3. checkEnterCourse / clearCheckPoint using CourseInfo now-world and now-course, and the enter type at CourseInfo+0x1E.
    // 4. Glyphs. Reads mGameData banner digits at FieldGameData+0x13D..+0x13F into CourseTask+0x134 and calls setGlyph.
    // 5. taskGameMode from the copied FieldGameData, including save byte +0x48 when sub_0250C3EC ran.
    // 6. Challenge. SubjectMgr and ChallengeMgr timers read course files from CourseInfo bytes, not save offsets.
    // After InputMgr::applySaveEntry_, the same mGameData buffer may change again when mode 1 or 2 calls sub_0250C3EC.
    // MainGame+0x88 is the save record pointer and the apply mode.
    // MainGame+0x2C is the story and pose flags for the CourseTask+0x28D gate.
    // story_bytes[0] and [2] feed the +0x304 world-bit gate.
    // MainGame+0x34 is PicturePaneMgr_lookupGlyph for CourseTask+0x264.
    // This function does not load player fields from the save itself.
    // Near the end (0x024BE210) it calls PlayerMgr::initializeForCourseSetup, then 0x02742F9C.
    // 0x02742F9C takes the same FieldGameData*. Its first argument is *(0x101EC398), the course owner singleton.
    // A direct open still has to seed CourseInfo next and now, MainGame+0x19C / +0x1A8 for the loading card,
    // FieldGameData+0x13D..+0x13F (map setCheckPoint does not fill those when the overworld enter is skipped),
    // and the FieldGame singleton that this memcpy copies.
    // Save apply at boot plus sub_0250C3EC covers most of that when record byte0 != 0.
    // Course setup does not replace enterMapFromGameData_ (0x024C2230) for the map return.
    // Address: 0x024BD86C
    void setupCourse();

    // Address: 0x024BCFC4
    void createGamesceneByMode();

    // Address: 0x024BCE88
    void setupNabbitEntry();

    // Address: 0x024BCFAC
    void setGlyph(s32 index, s8 value);

    // Address: 0x024C01DC
    void setSubjectClear();
    // Address: 0x024C01F4
    void setSubjectFail();

    GamesceneBase* getGamescene()
    {
        return mpGamescene;
    }

    // Address: 0x024C0D6C
    bool getGamesceneUnkBool() const;

    FieldGameData* getGameData()
    {
        return &mGameData;
    }

    const FieldGameData* getGameData() const
    {
        return &mGameData;
    }

    FieldPlayerData* getPlayerData(s32 index)
    {
        return &mGameData.getPlayerData(index);
    }

    const FieldPlayerData* getPlayerData(s32 index) const
    {
        return &mGameData.getPlayerData(index);
    }

    FieldGameMode::Mode getGameMode() const
    {
        return mGameData.getGameMode().getMode();
    }

    bool isMiniGame() const
    {
        return mGameData.getGameMode().isMiniGame();
    }

    void incEnemyDown(s32 player_no)
    {
        getPlayerData(player_no)->enemy_down_cnt++;
    }

private:
    bool            mCourseRestart;
    GamesceneBase*  mpGamescene;
    u32             _d0[(0x124 - 0xD0) / sizeof(u32)];
    FieldGameData   mGameData;
    u32             _308[(0x59C - 0x308) / sizeof(u32)];
    bool            mIsNabbitEntry;
    s32             mNabbitEntryIndex;
};
static_assert(sizeof(CourseTask) == 0x5A4);
