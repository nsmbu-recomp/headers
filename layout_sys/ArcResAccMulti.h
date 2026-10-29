#pragma once

#include <prim/seadSafeString.h>

class ArcResAccMulti
{
public:
    // Address: 0x0267B1DC
    static ArcResAccMulti* create(void* p_res_mgr, const sead::SafeString& res_name, const sead::SafeString& acc_name);

protected:
    u8 _00[0x3C];
};
static_assert(sizeof(ArcResAccMulti) == 0x3C);
