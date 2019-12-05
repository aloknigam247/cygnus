#include "fa.h"

#include "cytest.h"

class TestFA : public FA {
    public:
    void addTransition(char sym, bool is_final) {
        FA::addTransition(&m_state, sym)->is_final = is_final;
    }
};

void printFA() {
    TestFA f;
    f.addTransition('a', true);
    f.addTransition('b', false);
    f.printTPaths();
    f.printTGraph("out1");
}

int main() {
    cytest::Testcase testcase;
    testcase.add(printFA);
    testcase.run();
}
