#include <stdexcept>
#include <string>

#include "cystructs.h"

#include "cytest.h"

struct TestStruct {
    std::string name;
    TestStruct(std::string pi_name): name(pi_name) {}
    bool operator>(const TestStruct& pi_right) { return name > pi_right.name; }
    bool operator>(const char* pi_right)       { return name > pi_right;      }
    bool operator==(const char* pi_right)      { return name == pi_right;     }
};

void intType() {
    cystructs::Tree<int> t;
    t.insert(5);
}

void intPointer() {
    cystructs::Tree<int*> t;
    t.insert(new int(5));
    t.insert(new int(3));
    t.insert(new int(9));
    cystructs::Tree<int*>::iterator iter;
    try {
        iter = t.search(4);
        int* p = *iter;
    }
    catch(...) {
    }
    iter = t.search(9);
    if(iter != t.end())
        int* p = *iter;
    for(auto iter : t) {}
}

void objPointer() {
    cystructs::Tree<TestStruct*> t;
    t.insert(new TestStruct("test"));
    cystructs::Tree<TestStruct*>::iterator iter = t.search("test");
    std::string name = iter->name;
    try {
        iter = t.search("not exist");
        name = iter->name;
    }
    catch(...) {
    }
}

/* Just to give 100% coverage */
void refOf() {
    int i;
    const int ci = 10;
    cystructs::ref_of(i);
    cystructs::ref_of(ci);
}

int main() {
    cytest::Testcase testcase;
    testcase.add(intType);
    testcase.add(intPointer);
    testcase.add(objPointer);
    testcase.add(refOf);
    testcase.run();
}
