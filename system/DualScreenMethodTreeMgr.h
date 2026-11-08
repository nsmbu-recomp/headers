#pragma once

#include <basis/seadTypes.h>

namespace sead {

class MethodTreeNode;

class DualScreenMethodTreeMgr
{
public:
    // Calls the method-tree node at +0x40.
    // Address: 0x029FD93C
    void calc();

    // Calls the method-tree node at +0x13C. That node is the TV picture.
    // Address: 0x029FD944
    void drawTop();

    // Calls the method-tree node at +0x28C. That node is the GamePad picture.
    // Address: 0x029FD94C
    void drawBtm();
};

}
