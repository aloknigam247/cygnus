#include "nfa.h"

#include "log.h"

void NFA::addPattern(const char* patt) {
    m_patt_list.push_back(patt);
}

void NFA::compile() {
    for(auto patt: m_patt_list) {
        std::vector<int> curr, prev;
        curr.push_back(0);
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
                    curr.clear();
                    curr.push_back(addTransition(prev, patt[i]));
            }
        }
        for(auto curr_st: curr)
            table.set_final(curr_st);
    }
}

int NFA::execute(const char* word) {
    StateEntry* entry = table.get_entry(0);
    bool invalid;
    for(int i=0; word[i] != '\0'; ++i) {
        bool invalid = true;
        for(auto trans: entry->transition_list) {
            if(trans.sym == word[i]) {
                entry = table.get_entry(trans.state_id);
                invalid = false;
                break;
            }
        }
        if(invalid)
            return 0;
    }
    if(entry->is_final)
        return 1;
    return 0;
}
