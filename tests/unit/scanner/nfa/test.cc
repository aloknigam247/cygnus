#include "nfa.h"

#include "cytest.h"

void allSupportedPatterns() {
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
    nfa.printTable();
    nfa.printDot("nfa");
}

int main() {
    cytest::Testcase testcase;
    testcase.add(allSupportedPatterns);
    testcase.run();
}
