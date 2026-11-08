#pragma once

#include <basis/seadTypes.h>

// Guessed name.
// 0x0263020C in this area loads SaveDataSelect.bflyt.
// Each builder takes the file index in r4, strides records by 0x204, and calls copyFileSelectCourseFlags_.
class SaveDataSelect
{
public:
    // Guessed name.
    // File-select slot builder. The completion byte is at record+0x2E. Site 0x02631BE4 reads it.
    // Address: 0x02631B50
    void buildQuickSlot(u32 file);

    // Guessed name.
    // Second file-select slot builder. Site 0x0263ADD8 reads the same completion byte.
    // Address: 0x0263AD40
    void buildQuickSlotB(u32 file);

    // Guessed name.
    // File-copy preview. Compares the pane index with 6 and leaves that pane on the main record.
    // Site 0x02641A4C reads the completion byte.
    // Address: 0x02641974
    void buildCopySlot(u32 file);
};
