#pragma once

#include <game/FieldGameMode.h>
#include <game/FieldPlayerData.h>
#include <game/InfoStats.h>
#include <player/PlayerEnum.h>

#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>

struct CheckPointData
{
    s32     index;              // -1 when no checkpoint is set
    u8      world_no;           // Course to resume
    u8      course_no;
    u8      file_no;
    u8      next_goto_no;
    u32     _08;
    u8      _0c[2];             // Written at [index] for index < 2, else at [0]
    u8      _0e[2];             // Written at [index] for index < 2, else at [0]
    u8      banner_digit[3];
    u8      _13;
};
static_assert(sizeof(CheckPointData) == 0x14);

class FieldGameData
{
public:
    // Address: 0x024C1B04
    FieldGameData();

    FieldPlayerData& getPlayerData(s32 index)
    {
        return mPlayerData[index];
    }

    const FieldPlayerData& getPlayerData(s32 index) const
    {
        return mPlayerData[index];
    }

    s32 getPlayerCoinNum(s32 index) const
    {
        return mPlayerData[index].coin_cnt;
    }

    void setPlayerCoinNum(s32 index, s32 num)
    {
        mPlayerData[index].coin_cnt = num;
    }

    s32 getCoinNum() const
    {
        return mCoinNum;
    }

    const FieldGameMode& getGameMode() const
    {
        return mGameMode;
    }

    InfoStats& getStatsData()
    {
        return mStatsData;
    }

    const InfoStats& getStatsData() const
    {
        return mStatsData;
    }

    // Address: 0x024BAD4C
    void clearCheckPoint();

    // Address: 0x024BADCC
    s32 checkEnterCourse(u8 world_no, u8 course_no) const;

    // Address: 0x024BADF4
    void setCheckPoint(s32 index, u8 set_0c, u8 set_0e, u32 set_08,
                       u8 world_no, u8 course_no, u8 file_no, u8 next_goto_no,
                       const u8* banner_digit);

    // Map-enter call site 0x0250C76C (inside f_0250C3EC / InputMgr apply-save path):
    //   index      = (s8)save_entry[+0x43]
    //   set_0c     = (s8)save_entry[+0x44]
    //   set_0e     = 0
    //   set_08     = (s8)save_entry[+0x45]
    //   world/course/file from CourseInfo::mCourseNow (+0x10/+0x11/+0x12)
    //   next_goto  = save_entry[+0x46]
    //   banner     = FieldGameData banner digits at +0x13D (copied to stack)
    // Directed nsmbu open/run skips this path, so checkpoint index stays -1.

    // Address: 0x024C1DF0
    s32 searchEntryByCharacter(u32 character) const;

    // Address: 0x024C1E38
    FieldPlayerData* getEntryByCharacter(u32 character);

    // Address: 0x024C1E8C
    void swapEntries(s32 index_a, s32 index_b);

    // Address: 0x024C1F50
    void orderEntriesByCharacter(const u32* characters);

    // Address: 0x024C203C
    void setCoinNum(s32 num);

    // Address: 0x024C2044
    void resetEntriesUnk30();

    // Address: 0x024C2088
    void resetEntriesUnk2C();

    // Address: 0x024C20CC
    s32 searchEnteredEntryByCharacter(u32 character) const;

    // Address: 0x024C2148
    s32 getEnteredEntryNum() const;

private:
    CheckPointData      mCheckPoint;
    sead::SafeArray<
        FieldPlayerData,
        cPlayerNum
    >                   mPlayerData;
    s32                 mCoinNum;
    u32                 _138;           // Play seconds, written by the savedata sync (0x029D7A7C / 0x029D7CC8)
    u8                  _13c;
    u8                  mBannerDigit[3];
    u8                  _140;
    u8                  _141[3];
    u32                 _144[5];
    u32                 _158;
    FieldGameMode       mGameMode;
    u8                  _160[0x0C];
    s16                 _16c;
    u8                  _16e[4];
    u8                  _172[6];
    u32                 _178[5];
    u32                 _18c[5];
    s16                 _1a0;
    s16                 _1a2;
    u8                  _1a4;
    u8                  _1a5;
    u8                  _1a6[2];
    InfoStats           mStatsData;
    bool                _1e0;
};
static_assert(sizeof(FieldGameData) == 0x1E4);

class FieldGame
{
    // createInstance()                             Address: 0x024C2660
    // deleteInstance()                             Address: Deleted
    // sInstance                                    Address: 0x101D1604
    // SingletonDisposer_::~SingletonDisposer_()    Address: 0x024C26F4
    // SingletonDisposer_::sStaticDisposer          Address: 0x101D1608
    // SingletonDisposer_::vtbl                     Address: 0x100B7610
    SEAD_SINGLETON_DISPOSER(FieldGame)

public:
    FieldGameData& getGameData()
    {
        return mGameData;
    }

private:
    FieldGameData   mGameData;
};
static_assert(sizeof(FieldGame) == 0x1F4);
