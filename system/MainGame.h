#pragma once

#include <heap/seadDisposer.h>
#include <prim/seadBitFlag.h>

enum CourseExitType
{
    cCourseExitType_ChallengeRetry = 0,
    cCourseExitType_Exit,                   // e.g., from Pause menu
    cCourseExitType_Beaten,
    cCourseExitType_Dead,
    cCourseExitType_OtehonReplay,
    cCourseExitType_InsideCourse
};
static_assert(sizeof(CourseExitType) == 4);

enum CourseBeatenType
{
    cCourseBeatenType_Normal = 0,
    cCourseBeatenType_Secret,
    cCourseBeatenType_TreasureChest,
    cCourseBeatenType_TreasureChestFail     // Maybe for when Nabbit steals the treasure chest for idling too long on the ambush??
};
static_assert(sizeof(CourseBeatenType) == 4);

class MainGame
{
    // createInstance()                             Address: 0x029CDCAC
    // deleteInstance()                             Address: Deleted
    // sInstance                                    Address: 0x101E7D7C
    // SingletonDisposer_::~SingletonDisposer_()    Address: 0x029CEBF0
    // SingletonDisposer_::sStaticDisposer          Address: 0x101E7D80
    // SingletonDisposer_::vtbl                     Address: 0x1018A110
    SEAD_SINGLETON_DISPOSER(MainGame)

public:
    // Address: 0x029CD2E8
    MainGame();

    // Address: 0x029CEAD4
    void initMiiIconRenderBuffer(sead::Heap* heap = nullptr);

    bool isSinglePlayerDRC() const
    {
        return mIsSinglePlayerDRC;
    }

    bool isMultiplayer() const
    {
        return !mIsSinglePlayerDRC;
    }

    bool isNewGame() const
    {
        return mIsNewGame;
    }

    void setNewGame(bool new_game)
    {
        mIsNewGame = new_game;
    }

    bool isShadowkunQuest() const
    {
        return mIsShadowkunQuest;
    }

    CourseExitType getCourseExitType() const
    {
        return mCourseExitType;
    }

    void setCourseExitType(CourseExitType type)
    {
        mCourseExitType = type;
    }

    CourseBeatenType getCourseBeatenType() const
    {
        return mCourseBeatenType;
    }

    void setCourseBeatenType(CourseBeatenType type)
    {
        mCourseBeatenType = type;
    }

    bool isOtehon() const
    {
        return mReplayFlag.isOnBit(0);
    }

    bool isMapPoseValid() const
    {
        return mReplayFlag.isOnBit(3);
    }

    void setMapPoseValid(bool valid)
    {
        if (valid)
            mReplayFlag.setBit(3);
        else
            mReplayFlag.resetBit(3);
    }

    s32 getMapWorld() const { return mMapWorld; }
    s32 getMapSection() const { return mMapSection; }
    s32 getMapNodeIndex() const { return mMapNodeIndex; }
    s32 getMapCourse() const { return mMapCourse; }

    void setMapPose(s32 world, s32 section, s32 node_index, s32 course)
    {
        mMapWorld = world;
        mMapSection = section;
        mMapNodeIndex = node_index;
        mMapCourse = course;
    }

protected:
    u32                 _10;
    bool                mIsSinglePlayerDRC;
    u32                 _18;
    bool                mIsNewGame;
    CourseExitType      mCourseExitType;        // +0x20  set to 2 by requestCourseOut_Normal
    CourseBeatenType    mCourseBeatenType;      // +0x24
    u32                 _28;
    sead::BitFlag32     mReplayFlag;            // +0x2C  bit 3 (=8): map-pose gate for CourseSelectPlayer::create_
    u8                  _30[(0x19C - 0x30)];
    s32                 mMapWorld;              // +0x19C  world index for map return pose
    s32                 mMapSection;            // +0x1A0  section (0/1); path idx = (world<<1)+section
    s32                 mMapNodeIndex;          // +0x1A4  node index in CourseSelectNodePath
    s32                 mMapCourse;             // +0x1A8  course tag (pack course no), not node+0x50
    u8                  _1ac[(0x82E - 0x1AC)];
    bool                mIsNabbitEntry;
    bool                mIsNabbitEntryMii;
    u8                  _830[(0x21DDC - 0x830)];
    u8                  _21ddc[30];
    bool                mIsShadowkunQuest;
    u32                 _21dfc[(0x21E18 - 0x21DFC) / sizeof(u32)];
};
static_assert(sizeof(MainGame) == 0x21E18);
