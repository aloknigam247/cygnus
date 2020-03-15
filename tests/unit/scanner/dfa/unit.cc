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
    nfa.printTable();

    DFA dfa = nfa;
    dfa.printTable();
    dfa.printDot("case1");

    const char *s = "ssssss";
    if(dfa.execute(s))
        cytest::Log::i(s, ": Accept");
    else
        cytest::Log::i(s, ": Reject");

    s = "qqq";
    if(dfa.execute(s))
        cytest::Log::i(s, ": Accept");
    else
        cytest::Log::i(s, ": Reject");

    s = "";
    if(dfa.execute(s))
        cytest::Log::i(s, ": Accept");
    else
        cytest::Log::i(s, ": Reject");

    s = "rRsss";
    if(dfa.execute(s))
        cytest::Log::i(s, ": Accept");
    else
        cytest::Log::i(s, ": Reject");
}

void emptyDFA() {
    NFA nfa;
    DFA dfa = nfa;
    dfa.execute(nullptr);
}

int main() {
    cytest::Testcase testcase;
    testcase.add(convertNFA2DFA);
    testcase.add(emptyDFA);
    testcase.run();
}
