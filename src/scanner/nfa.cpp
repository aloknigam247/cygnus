#include "nfa.h"

#include "cstdlib"
#include "fstream"

#include "log.h"

void NFA::addPattern(std::string patt) {
    m_patt_list.push_back(patt);
}

void NFA::compile() {
    for(auto patt: m_patt_list) {
        Log::d(patt);
        State* cur = &m_state;
        for(auto c: patt) {
            Log::d(c);
            cur = move(cur, c);
        }
        cur->is_final = true;
    }
}

void NFA::execute() {
}

void NFA::printStates() {
    State* cur = &m_state;
    while(cur->next) {
        std::cout << 'q' << cur->id  << "--" << cur->input_sym << "-->";
        cur = cur->next;
    }
    std::cout << 'q' << cur->id << '\n';
}

void NFA::printDot() {
    State* cur = &m_state;
    std::ofstream dotfile("dotfile");
    dotfile << 
R"(digraph nfa {
    rankdir=LR;
)";
    while(cur->next) {
        dotfile << "    "<< 'q' << cur->id  << " -> ";
        if(cur->next->is_final)
            dotfile << "{node [shape=doublecircle] q" << cur->next->id << " }";
        else
            dotfile << 'q' << cur->next->id;
        dotfile << " [label=\"" << cur->input_sym << "\"]\n";
        cur = cur->next;
    }
    dotfile << "}\n";
    dotfile.close();

    std::system("dot -Tpng dotfile > t.png");
}

State* NFA::move(State* from, char sym) {
    static int state_id=1;
    from->next = new State(state_id++);
    from->input_sym = sym;
    return from->next;
}
