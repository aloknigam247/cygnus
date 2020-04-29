#ifndef SCANNER_DFA_H
#define SCANNER_DFA_H

#include "scanner/nfa.h"

class DFA: public FA {
    public:
        DFA(NFA nfa);
        bool execute(const char* word);
};

#endif
