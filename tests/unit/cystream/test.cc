#include "test.h"
#include "cycase.h"
#include "CyStream.h"

void case1() {
    CyStream st;
    st.open("testFile", std::ios_base::out);
    st.close();
}

void case2() {
    CyStream st;
    st.open("testFile", std::ios_base::out);
}

void case3() {
    CyStream st;
    st.open("no_exist", std::ios_base::in);
}

int main() {
    Testcase t;
    t.add(case1);
    t.add(case2);
    t.add(case3);
    t.run();
    return 0;
}
