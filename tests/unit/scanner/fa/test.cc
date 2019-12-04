#include "fa.h"

#include "cytest.h"

class TestFA : public FA {
    public:
    State* m_state;
    TestFA(): m_state(nullptr) {
        m_state = &FA::get_state();
    }
    void addTransition(char sym, bool is_final) {
        m_state = FA::addTransition(m_state, sym);
        m_state->is_final = is_final;
    }
};

void printFA() {
    TestFA f;
    f.addTransition('a', false);
    f.addTransition('b', true);
    f.printTPaths(f.get_state());
    f.printTGraph();
}

int main() {
    cytest::Testcase testcase;
    testcase.add(printFA);
    testcase.run();
}
