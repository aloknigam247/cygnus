#include "status.h"

extern "C" {
#include <ncurses.h>
}

class CyUI {
    public:
    Status init();
    void end();

    private:
    WINDOW *stdscr = nullptr;
};
