#include "nfa.h"

#include "log.h"

void NFA::addPattern(const char* patt) {
    m_patt_list.push_back(patt);
}

void NFA::compile() {
    for(auto patt: m_patt_list) {
        Log::d("Pattern: ", patt);
        std::vector<State*> curr;
        curr.push_back(&m_state);
        std::vector<State*> prev;
        int i=0;
        while(patt[i]!='\0') {
            Log::d("  Look: ", patt[i]);
            switch(patt[i]) {
                case '+':
                    /* Apply + */
                    Log::d("    Modifier: ", patt[i]);
                    addTransition(curr.front(), patt[i-1], curr.front());
                    ++i;
                    break;
                case '?':
                    /* Apply ? */
                    Log::d("    Modifier: ", patt[i]);
                    curr.push_back(prev.front());
                    ++i;
                    break;
                case '*':
                    /* Apply * */
                    Log::d("    Modifier: ", patt[i]);
                    addTransition(curr.front(), patt[i-1], curr.front());
                    curr.push_back(prev.front());
                    i++;
                    break;
                default:
                    prev = move(curr);
                    curr = addTransition(prev, patt[i]);
                    i++;
            }
        }
        for(auto curr_st: curr)
            curr_st->is_final = true;
    }
}
