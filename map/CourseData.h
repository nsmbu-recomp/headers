#pragma once

#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <math/seadBoundBox.h>

struct Options
{
    // Official name not known, but is called area options by the modding community.

    u32 course_default_switch_flags;
    u32 file_default_switch_flags;
    u16 loop;
    u16 time_0;
    u8  _unused0[4];
    u8  start_next_goto;
    u8  _unused1[2];
    u8  start_next_goto_coin_boost;
    u16 time_1;
    u16 time_2;
};
static_assert(sizeof(Options) == 0x18);

struct DistantViewData
{
    // Not certain if official name, but official name in NSMBW is Bg2 (which is conflicting with tile layers)

    u16     id;
    struct
    {
        s16 x;
        s16 y;
        s16 z;
    }       offset;         // Unused
    char    name[16];
    u16     parallax_mode;  // Unused
    u8      _pad[2];
};
static_assert(sizeof(DistantViewData) == 0x1C);

struct NextGoto
{
    // Is the official name. Called entrance by the modding community.

    struct
    {
        u16 x;
        u16 y;
    }   offset;
    struct
    {
        u16 x;
        u16 y;
    }   camera_offset;
    u8  id;
    struct
    {
        u8  file;
        u8  next_goto;
    }   destination;
    u8  type;
    u8  mp_spawn_flag;
    u8  area;
    u8  _unused0;
    u8  mp_inner_gap;
    u16 flag;
    u8  chibi_yoshi_next_goto;
    u8  coin_edit_priority;
    struct
    {
        u8 info;
        u8 point;
    } rail;
    u8  wipe_type;
    u8  _pad[1];
};
static_assert(sizeof(NextGoto) == 0x18);

struct MapActorData
{
    // Speculated official name.

    u16 type;
    struct
    {
        u16 x;
        u16 y;
    }   offset;
    u16 switch_flags;   // Lower byte: switch flag 0, higher byte: switch flag 1.
    u32 param_0;
    u32 param_1;
    u8  area;
    u8  layer;
    u8  movement_id;
    u8  link_id;
    u8  init_state;
    u8  _pad[3];
};
static_assert(sizeof(MapActorData) == 0x18);

struct AreaData
{
    // Is the official name. Called "zone" by the modding community.

    // NSMBW
    struct
    {
        u16 x;
        u16 y;
    }   offset;
    struct
    {
        u16 x;
        u16 y;
    }   size;
    u16 color_obj;      // "Theme", unused.
    u16 color_bg;       // "Terrain", unused.
    u8  id;
    u8  scroll;
    u8  zoom_type;
    u8  zoom_id;
    u8  zoom_change;
    u8  mask;
    u8  bg2;            // 1st BG id in NSMBW, DV ID in NSMBU.
    u8  bg3;            // 2nd BG id in NSMBW, unused.
    u8  direction;
    u8  _15;
    u8  bgm;
    u8  bgm_mode;

    // NSMB2
    u8  dv;             // DV ID in NSMB2, unused.

    // NSMBU
    u8  flag;
    u8  _pad[2];
};
static_assert(sizeof(AreaData) == 0x1C);

struct Location
{
    // Official name not known.

    struct
    {
        u16 x;
        u16 y;
    }   offset;
    struct
    {
        u16 x;
        u16 y;
    }   size;
    u8  id;
    u8  _pad[3];
};
static_assert(sizeof(Location) == 0xC);

struct RailInfo
{
    // Not certain if official name.

    u8  id;
    s8  _1;
    struct
    {
        u16 start;
        u16 num;
    }   point;
    u16 flag;
    u32 _8;
};
static_assert(sizeof(RailInfo) == 0xC);

struct RailPoint
{
    // Official name not known.

    struct
    {
        u16 x;
        u16 y;
    }   offset;
    f32 speed;
    f32 accel;
    s16 delay;

    // Nabbit-related
    u16 _e;
    u8  _10;
    u8  _11;
    u8  _12;
    u8  _pad[1];
};
static_assert(sizeof(RailPoint) == 0x14);

class CourseDataFile
{
    // Is the official name. Called "area" by the modding community.

public:
    enum Block
    {
        cBlock_Environment      =   1 - 1,
        cBlock_Options          =   2 - 1,
        cBlock_ScrollData       =   3 - 1,
                                //  4
        cBlock_DistantViewData  =   5 - 1,
                                //  6
        cBlock_NextGoto         =   7 - 1,
        cBlock_MapActor         =   8 - 1,
        cBlock_MapActorLoadRes  =   9 - 1,
        cBlock_AreaData         =  10 - 1,
        cBlock_Location         =  11 - 1,
                                // 12
                                // 13
        cBlock_RailInfo         =  14 - 1,
        cBlock_RailPoint        =  15 - 1,
        cBlock_Num
    };

public:
    CourseDataFile();

    // Address: 0x0269972C
    // Fills mBlock (+0x04), mBlockSize (+0x40), and mBlockEntryNum (+0x7C) from the element size table at 0x100E5FCC.
    // The table is one u32 per block. The file is one blob split on those sizes.
    // Confirmed sizes: 0 = 0x80 environment, 1 = 0x18 options, 2 = 0x1C scroll,
    // 3 = 0x08, 4 = 0x1C distant view, 5 = 0x14, 6 = 0x18 next goto, 7 = 0x18 map actor,
    // 8 = 0x04 map actor load res, 9 = 0x1C area, 10 = 0x0C location, 11 = 0x18, 12 = 0x18,
    // 13 = 0x0C rail info, 14 = 0x14 rail point.
    // Subtracts 4 from the block 7 size before the entry count, so the map actor block has a 4 byte header in the file.
    // Block matches this table, so the cBlock_* indices are the file indices.
    void registerBlocks(const void* image);

    const void* getBlock(Block block)
    {
        return mBlock[block];
    }

    const DistantViewData* getBg2Data(u16 id) const;

    // Address: 0x02699BD8
    // Base +0x1C, count +0x94, stride 0x18, id byte at +0x08.
    const NextGoto* getNextGoto(u8 id) const;

    // Address: 0x02699C08
    // Base +0x20, count +0x98, stride 0x18, type u16 at +0x00.
    // p_start resumes at p_start + 0x18.
    const MapActorData* getMapActor(u16 type, const MapActorData* p_start = nullptr) const;

    const AreaData* getAreaData(u8 id, sead::BoundBox2f* p_box = nullptr) const;

    // Address: 0x0269A020
    // Base +0x2C, count +0xA4, stride 0x0C, id byte at +0x08.
    // Also calls the area box builder 0x02699F70 with a delta of 0.0f when p_box != nullptr.
    // 0x02699F70 takes the same fields as getAreaBox_ but takes separate x and y deltas, which are equal at every call site.
    const Location* getLocation(sead::BoundBox2f* p_box, u8 id) const;

    // Address: 0x0269A0A8
    // Base +0x38, count +0xB0, stride 0x0C, id byte at +0x00.
    // Returns nullptr when the block is not loaded.
    const RailInfo* getRailInfo(u8 id) const;

    // Address: 0x0269A0F4
    // getRailInfo(rail_id), then block 14 + rail->point.start * 0x14.
    const RailPoint* getRailPoint(u8 rail_id) const;

private:
    void getAreaBox_(sead::BoundBox2f* p_box, const AreaData& area_data, f32 delta = 0.0f) const;

private:
    u32                                         mIndex;
    sead::SafeArray<const void*,    cBlock_Num> mBlock;
    sead::SafeArray<u32,            cBlock_Num> mBlockSize;
    sead::SafeArray<u32,            cBlock_Num> mBlockEntryNum;
    sead::SafeArray<MapActorData*,  64>         _b8;
    sead::SafeArray<u32,            64>         _1b8;
    sead::SafeArray<u32,            64>         _2b8;
};
static_assert(sizeof(CourseDataFile) == 0x3B8);

class CourseData
{
    // instance()       Address: 0x0269A1B0
    // sInstance        Address: 0x101EB048, 0x101EB04C
    // ~CourseData()    Address: 0x0269A304
    SEAD_SINGLETON_DISPOSER(CourseData)

public:
    // Address: 0x0269A144
    // Builds the four files with sub_02AFA350(mFile, 4, 0x3B8, 0x026A94FC).
    // CourseData is 0xEF0 bytes: a SEAD_SINGLETON_DISPOSER prefix of 0x10 and mFile at +0x10.
    CourseData();
    ~CourseData();

    // Address: 0x0269A244
    void loadRecordCourseFiles();

    // Address: 0x0269A2DC
    // Clamps an out-of-range index to element 0 ((u32)index >= 4).
    // Returns nullptr when the file has no area data block (block 9).
    // The rpx symbol map names this address CourseData::getFile.
    CourseDataFile* getFileIfLoaded(s32 index) const;

    CourseDataFile* getFile(s32 index);

private:
    sead::SafeArray<CourseDataFile, 4> mFile;
};
static_assert(sizeof(CourseData) == 0xEF0);
