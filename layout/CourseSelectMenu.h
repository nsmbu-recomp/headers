#pragma once

#include <layer/aglRenderInfo.h>

class CourseSelectMenu
{
public:
    // Builds the world-map start menu.
    // Both files live in Common/layout/CourseSelect.szs.
    // The byte at the object from 0x101E7D9C, offset 0x11, selects the layout file.
    // One branch builds through the name at 0x100DEF38.
    // The other branch builds through the name at 0x100DEF54.
    // Those names are CourseSelectMenu.bflyt and CourseSelectMenuDL.bflyt.
    // The layout object is the AnimLayoutBase at +0x28.
    // Build returns the .bflyt bytes in r3. The file name is not still in a register there.
    // The port recognizes this menu by the Pa_TitleBtn_00 pane and may insert Pa_SetBtn_00 before the file is parsed.
    // PaPaneRegister stores ten part pointers at this+0x11E8, in this order:
    // Pa_SCoinBtn_00, Pa_NumBtn_00, Pa_SuspendBtn_00, Pa_TitleBtn_00, Pa_SaveBtn_00,
    // Pa_PlayStyleBtn_00, Pa_SetUp_00, Pa_SetUp_01, Pa_Olieve_00, Pa_Close_00.
    // Under N_Btn_00 at (0, 25), the top row is local x = -424, 0, 424 and y = 114.
    // The bottom row is a centered pair at y = -114: Quick Save (Pa_SuspendBtn_00 and Pa_SaveBtn_00, one shown) near x = -213,
    // and Main Menu (Pa_TitleBtn_00) near x = 212.
    // The object does not have a sixth button handler.
    // The function then constructs the PaCursor at +0xEC8.
    // The current index is at PaCursor+0x250.
    // The common pad mask the cursor reads is at PaCursor+0x164 (Plus = bit 11, Touch = bit 12, Decide = bit 13, Back = bit 14).
    // Enter is Plus. A is Decide.
    // Address: 0x025A42CC
    void create();

    // Steps the open menu for one frame.
    // A zero byte at +0x1A04 returns before any of this work. The menu runs its body only when that byte is non-zero.
    // While PaCursor+0x25C is 0, a window such as Change Controller owns the pad.
    // A button word other than 0 sets PaCursor+0x268.
    // The idle state at 0x025A51EC reads PaCursor+0x25E before PaCursor::execute.
    // While that byte is clear, the pad word at +0x1214 picks the next cursor index.
    // Index 6 with the left bit goes to index 8 only when +0x1A0B is set. Otherwise left does nothing.
    // The up bit from index 6 goes to index 5.
    // A clear byte plus Decide on the menu pad calls PaCursor::triggerDecide and enters 0x10211B34.
    // That state's execute is 0x025A5420. It stores the action for the cursor index at +0x24 and enters 0x10211B54.
    // 0x10211B54 starts OutBtn with Multi2D::animStartSetup. When the animator ends, its execute enters the stored action.
    // Index 6 and index 7 both store 0x10211BD4. That action opens Button Settings.
    // 0x10211DF4 starts InBtn and, when that animator ends, returns to the idle state 0x10211B14.
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
