#include "fa.h"

#include "cytest.h"

class TestFA : public FA {
    public:
    void addTransition(const char *sym_list) {
        int last_state=0;
        for(int i=0; sym_list[i]!='\0'; ++i) {
            last_state = FA::addTransition(last_state, sym_list[i]);
        }
        state_list.push_back(last_state);
    }

    void setEndWord(char c) {
        int state = FA::addTransition(state_list, c);
        get_table().set_final(state);
    }

    private:
    std::vector<int> state_list;
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
    f.setEndWord('$');
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

void hiddenChar() {
    TestFA f;
    char hidden[3] = {92, 127, '\0'};
    f.addTransition(hidden);
    f.setEndWord('$');
    f.printTable();
    f.printDot("case3");
}

void hundredStates() {
    TestFA f;
    char str[99];
    for(int i=0; i<99; ++i)
        str[i] = 'a';

    f.addTransition(str);
    f.setEndWord('$');
    f.printTable();
    f.printDot("case4");
}

int main() {
    cytest::Testcase testcase;
    testcase.add(emptyFA);
    testcase.add(printFA);
    testcase.add(hiddenChar);
    testcase.add(hundredStates);
    testcase.run();
}
