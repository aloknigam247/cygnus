#ifdef EXTENDED_FEATURE

#ifndef SCANNER_DFA_H
#define SCANNER_DFA_H

#include "nfa.h"

class DFA: public FA {
    public:
        DFA(NFA nfa);
        bool execute(const char* word);
};

#endif

#endif
