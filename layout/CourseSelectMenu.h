#pragma once

#include <layer/aglRenderInfo.h>

class CourseSelectMenu
{
public:
    // Builds the world-map start menu.
    // The byte at the object from 0x101E7D9C, offset 0x11, selects the layout file.
    // One branch builds through the name at 0x100DEF38.
    // The other branch builds through the name at 0x100DEF54.
    // Those names are CourseSelectMenu.bflyt and CourseSelectMenuDL.bflyt.
    // The layout object is the AnimLayoutBase at +0x28.
    // The function then constructs the PaCursor at +0xEC8.
    // Address: 0x025A42CC
    void create();

    // Steps the open menu for one frame.
    // A zero byte at +0x1A04 returns before any of this work.
    // The call runs StateMethod::executeStateMethod on the state at +0x10.
    // It then runs PaCursor::execute on the cursor at +0xEC8.
    // It finishes with Multi2D::animPlay on the layout at +0x28, view layer 0xE.
    // A change in the byte at +0x1A0F also calls Multi2D::setTextBoxMessageFromTextID.
    // Address: 0x025A4B98
    void execute();

    // Draws the menu layout.
    // A zero byte at +0x1A06 returns before the draw.
    // The draw uses the AnimLayoutBase at +0x28.
    // Address: 0x025A4C94
    void draw(const agl::lyr::RenderInfo& render_info) const;

    // Destroys the five objects at +0x1214, then the PaCursor, then the layout.
    // The low bit of the destructor flag also deletes this object.
    // Address: 0x025A4218
    virtual ~CourseSelectMenu();
};
