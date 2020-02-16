#include "fa.h"

#include "cytest.h"

class TestFA : public FA {
    public:
    void addTransition(const char *sym_list, bool is_final) {
        int last_state=0;
        for(int i=0; sym_list[i]!='\0'; ++i) {
            last_state = FA::addTransition(last_state, sym_list[i]);
        }
    }

    private:
};

void emptyFA() {
    TestFA f;
    f.printTable();
    f.printGraph("out1");
}

void printFA() {
    TestFA f;
    f.addTransition("abc", true);
    f.addTransition("xyz", false);
    f.printTable();
    f.printGraph("out2");
}

int main() {
    cytest::Testcase testcase;
    testcase.add(emptyFA);
    testcase.add(printFA);
    testcase.run();
}
