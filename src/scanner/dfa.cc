#include "dfa.h"

DFA::DFA(NFA nfa) {
    table = nfa.get_table();
    int t_size = table.size();
    int n_state = t_size;

    State *t;
    for(int i=0; i<t_size; ++i) {
        State *s = &(table.row[i]);
        for(int j=0; j<128; ++j) {
            if(s->sym[j].size() <= 1)
                continue;
            for(auto a: s->sym[j]) {
                t = table.get_state(a);
                for(int k=0; k<128; ++k) {
                    if(t->sym[k].empty())
                        continue;
                    addTransition(n_state, k, t->sym[k].front());
                }
                s = &(table.row[i]);   // s points wrong when vector is resized
            }
            s->sym[j].clear();
            addTransition(i, j, n_state++);
        }
    }
}

bool DFA::execute(const char* word) {
    if(!word)
        return false;

    State curr = table.row[0];

    for(int i=0; word[i]!='\0'; ++i) {
        std::vector<int> n_state = curr.sym[word[i]];
        if(n_state.empty())
            return false;

        curr = table.row[n_state.front()];
    }

    if(curr.final_state)
        return true;
    return false;
}
