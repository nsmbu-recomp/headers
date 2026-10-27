#pragma once

#include <basis/seadTypes.h>

namespace sead { class Heap; }

class CourseSelectLayerMgr
{
public:
    // sInstance                                    Address: 0x101E8A2C
    static CourseSelectLayerMgr* instance()
    {
        return sInstance;
    }

    // Address: 0x021EE9E4
    static void createLayers(sead::Heap* heap);

private:
    static CourseSelectLayerMgr* sInstance;
};
