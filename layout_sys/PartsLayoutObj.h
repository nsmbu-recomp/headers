#pragma once

#include <layout_sys/LayoutObj.h>
#include <layout_sys/TextBox.h>

#include <nw/lyt/lyt_Bounding.h>
#include <nw/lyt/lyt_Picture.h>

#include <prim/seadSafeString.h>

class PartsLayoutObj : public LayoutObj
{
public:
    // Address: 0x0267A188
    TextBox* findTextBoxByName_(const sead::SafeString& name);

    // Address: 0x0267A2E4
    nw::lyt::Bounding* findBoundingByName_(const sead::SafeString& name);

    // Address: 0x0267A414
    nw::lyt::Picture* findPictureByName_(const sead::SafeString& name);

protected:
    u8 _34[0x48 - 0x34];
};
static_assert(sizeof(PartsLayoutObj) == 0x48);
