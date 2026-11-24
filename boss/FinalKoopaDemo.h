#pragma once

#include <boss/BossDemo.h>

class FinalKoopaDemo : public BossDemo  // vtbl Address: 0x10016AF0
{
    SEAD_RTTI_OVERRIDE(FinalKoopaDemo, BossDemo)

public:
    // Looks up the first live FinalKoopaJr actor and confirms it is an Actor.
    // Address: 0x02093F20
    Actor* bossSearch() override;
};