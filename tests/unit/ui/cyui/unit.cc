#include "cytest.h"
#include "cyui.h"

void init() {
    CyUI ui;

    ui.init();
    ui.end();
}

int main() {
    cytest::Testcase testcase;
    testcase.add(init);
    testcase.run();
    return 0;
}
