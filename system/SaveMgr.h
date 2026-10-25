#pragma once

#include <heap/seadDisposer.h>
#include <thread/seadDelegateThread.h>

struct SaveData
{
    struct
    {
        u32 magic;
        u8  version_major;
        u8  version_minor;
        u8  version_patch;
        u8  last_file;
        u8  rdash_state;    // 1 -> The game has notified you about the NSLU DLC.
        u8  set_up;         // AB/XY & AX/BY setup
        u8  padding[2];
        u32 crc32;
    }   header;
    u32 _10[(0xB134 - 0x10) / sizeof(u32)];
};
static_assert(sizeof(SaveData) == 0xB134);

struct FFLStoreData;

// Address: 0x029E2924
bool checkSavedataBlockCrc(const void* block, u32 size);

// Address: 0x029E2994
void writeSavedataBlockCrc(void* block, u32 size);

// Address: 0x029D7CC8
void writeDefaultGameDataToRecords_(SaveMgr* mgr);

class SaveMgr
{
    SEAD_SINGLETON_DISPOSER(SaveMgr)

public:
    enum Status
    {
        cStatus_Ready = 0,
        cStatus_Reading,
        cStatus_Writing
    };
    static_assert(sizeof(Status) == 4);

    enum ReadError
    {
        cReadError_OK                       = 0,
        cReadError_FileDeviceUnavailable    = 1,
        cReadError_FileUnavailable          = -1,
        cReadError_FileInvalid              = -2
    };
    static_assert(sizeof(ReadError) == 4);

    enum WriteError
    {
        cWriteError_OK                      = 0,
        cWriteError_FileDeviceUnavailable   = -1,
        cWriteError_FileWriteFailed         = -2
    };
    static_assert(sizeof(WriteError) == 4);

public:
    SaveMgr();
    virtual ~SaveMgr();

    bool isSaving() const
    {
        return mStatus == cStatus_Writing || _30 != -1;
    }

    bool isSavingDone() const
    {
        return mStatus != cStatus_Writing;
    }

    const FFLStoreData& getStoreData(s32 index) const;

    // Address: 0x029D8C10
    // File confirm calls this after applySaveFile. The live snapshot reads
    // MainGame fields that still hold the previous story record, then the
    // quick record at +0xC28 is cleared and the buffer is written. The runtime
    // copies the quick record over that snapshot when the snapshot did not move.
    void startSaveGame(u8 file);

    // Address: 0x029D8478
    // 0x02987200 calls this with the header's last file when that file is opened.
    // It clears the quick record and writes the buffer, leaving the story record
    // unchanged. The runtime copies the quick record onto the story record first.
    void clearQuickAndWrite(u8 file);

    // Address: 0x029D8C7C
    void startQuickSaveGame(u8 file);

    void startSaveGame()
    {
        startSaveGame(mpSavedata->header.last_file);
    }

    void startQuickSaveGame()
    {
        startQuickSaveGame(mpSavedata->header.last_file);
    }

    // Address: 0x029D8270
    void startReadGame();

    // Address: 0x029D8304
    void startWriteGame();

    // Address: 0x029D82A0
    void startReadChallengeReplay(void* param);

    // Address: 0x029D8E88
    void startWriteChallengeReplay(void* param);

    // Address: 0x029D82D4
    void startReadPersonalSavedata();

    // Address: 0x029D8394
    void startWritePersonalSavedata();

protected:
    // Address: 0x029D914C
    void loadSavedata();

    // Address: 0x029D94C4
    void updatePlayTime();

    // Address: 0x029D9560
    void saveSavedata();

    // Address: 0x029D97BC
    void loadChallengeReplay();

    // Address: 0x029D994C
    void saveChallengeReplay();

    // Address: 0x029D9AD8
    void loadPersonalSavedata();

    // Address: 0x029D9CBC
    void savePersonalSavedata();

    // Address: 0x029D9E30
    void runState(u32 state);

    sead::DelegateThread*   mpDelegateThread;
    Status                  mStatus;
    ReadError               mReadError;
    WriteError              mWriteError;
    s32                     _20;                    // enum ?
    const SaveData*         mpSavedata;             // rp_savedata
    void*                   mpPersonalSavedata;     // rp_personal_savedata
    bool                    mButtonLayoutChanged;
    u8                      _2d;
    u8                      _2e;
    u8                      _2f;
    s32                     _30;
    s64                     mInitTime;              // sead::DateTime
    s64                     mStoryPlayInitTime;     // sead::DateTime

};
static_assert(sizeof(SaveMgr) == 0x50);
