#include "cyui.h"

Status CyUI::init() {
    stdscr = initscr();
    return Status::SUCCESS;
}

void CyUI::end() {
    endwin();
}
