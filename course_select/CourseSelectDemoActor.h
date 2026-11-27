#pragma once

#include <actor/ActorCreateParam.h>

// Guest object, size 0x108. Fields are stored at guest offsets.
class CourseSelectDemoActor
{
public:
    // Address: 0x021D4CB4
    CourseSelectDemoActor(const ActorCreateParam& param);
};
