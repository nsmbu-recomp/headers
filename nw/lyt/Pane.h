#pragma once

namespace nw { namespace lyt {

class DrawInfo;

class Pane
{
public:
    // Builds this pane's matrix. A widescreen edge anchor is applied once per pane.
    // Address: 0x02ABC054
    void CalculateMtx(const DrawInfo& draw_info);

    // Draws this pane when it is visible, then walks its children.
    // The DrawSelf call is the instruction at 0x02ABCB34. The child walk starts at 0x02ABCB38.
    // Address: 0x02ABCAE8
    void Draw(const DrawInfo& draw_info);
};

} }
