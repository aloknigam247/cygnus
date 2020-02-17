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
