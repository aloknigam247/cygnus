#include "fa.h"

#include "cytest.h"

class TestFA : public FA {
    public:
    void addTransition(const char *sym_list) {
        int last_state=0;
        for(int i=0; sym_list[i]!='\0'; ++i) {
            last_state = FA::addTransition(last_state, sym_list[i]);
        }
        get_table().set_final(last_state);
    }
};

void emptyFA() {
    TestFA f;
    f.printTable();
    f.printDot("case1");
}

void printFA() {
    TestFA f;
    f.addTransition("abc");
    f.addTransition("xyz");
    f.printTable();
    f.printDot("case2");

    StateTable &tab = f.get_table();
    int s = tab.size();
    int final_states = 0;
    for(int i=0; i<s; ++i) {
        if(tab.get_state(i)->final_state)
            ++final_states;
    }

    std::cout << "Size of Table: " << s << '\n';
    std::cout << "Number of final states: " << final_states << '\n';;
}

int main() {
    cytest::Testcase testcase;
    testcase.add(emptyFA);
    testcase.add(printFA);
    testcase.run();
}
