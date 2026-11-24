#pragma once

#include <boss/Boss.h>

class FinalKoopaJrBase : public Boss    // vtbl Address: Deleted
{
    // getRuntimeTypeInfoStatic()::typeInfo initialization guard variable   Address: 0x101FA084
    // getRuntimeTypeInfoStatic()::typeInfo                                 Address: 0x101FA080
    SEAD_RTTI_OVERRIDE(FinalKoopaJrBase, Boss)
};

class FinalKoopaJr : public FinalKoopaJrBase    // vtbl Address: 0x10017E28
{
    // getRuntimeTypeInfoStatic()::typeInfo initialization guard variable   Address: 0x101FA08C
    // getRuntimeTypeInfoStatic()::typeInfo                                 Address: 0x101FA088
    SEAD_RTTI_OVERRIDE(FinalKoopaJr, FinalKoopaJrBase)

public:
    // Returns whether the queried type is this actor or a base RTTI slot in its chain.
    // Address: 0x020A4C50
    bool isKindOf(const sead::RuntimeTypeInfo& type) const override;
};