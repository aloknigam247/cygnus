#include "nfa.h"

void NFA::addPattern(const char* patt) {
    m_patt_list.push_back(patt);
}

void NFA::compile() {
    for(auto patt: m_patt_list) {
        std::vector<State*> curr, prev;
        curr.push_back(&m_state);
        for(int i=0; patt[i]!='\0'; ++i) {
            switch(patt[i]) {
                case '+':
                    addTransition(curr.front(), patt[i-1], curr.front());
                    break;
                case '?':
                    curr.push_back(prev.front());
                    break;
                case '*':
                    addTransition(curr.front(), patt[i-1], curr.front());
                    curr.push_back(prev.front());
                    break;
                default:
                    prev = move(curr);
                    curr = addTransition(prev, patt[i]);
            }
        }
        for(auto curr_st: curr)
            curr_st->is_final = true;
    }
}
