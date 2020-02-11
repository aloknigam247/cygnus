#include "cytest.h"

#include "nfa.h"

#include "dfa.h"

void convertNFA2DFA() {
    NFA nfa;
    nfa.addPattern("r");
    nfa.addPattern("p+");
    //nfa.addPattern("+");
    nfa.addPattern("q?");
    //nfa.addPattern("?");
    nfa.addPattern("s*");
    //nfa.addPattern("*");
    nfa.addPattern("rRs*Sq?Qp+PD");
    nfa.build();

    DFA dfa = nfa;
    dfa.printTable;
    dfa.printGraph("dfa");
}

int main() {
    cytest::Testcase testcase;
    testcase.add(convertNFA2DFA);
    testcase.run();
}
