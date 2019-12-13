#include "fa.h"

#include <cstdlib>
#include <cstring>
#include <iostream>

void StateTable::addEntry(int from, char sym, int to) {
    if(!state_entry[from])
        state_entry[from] = new StateEntry;

    if(state_entry[from]->tag.size() == 1)
        state_entry[from]->tag += std::to_string(from);

    state_entry[from]->transition_list.push_back(StateEntry::Transition{sym, to});

    if(!state_entry[to]) {
        state_entry[to] = new StateEntry;
        state_entry[to]->tag += std::to_string(to);
    }
}

void StateTable::print() {
    std::cout << "index\ttag\tfinal\tsym\tto...\n";
    for(int i=0; i<state_entry.size(); ++i) {
        if(state_entry[i]) {
            StateEntry* entry = state_entry[i];
            std::cout << i << '\t';
            std::cout << entry->tag << '\t' << entry->is_final << '\t';
            for(auto transition: entry->transition_list) {
                std::cout << transition.sym << '\t' << transition.state_id << '\t';
            }
            std::cout << "\n";
        }
    }
}

void StateTable::printDot(std::ofstream& file) {
    file << "digraph fa {\n"
         << "    rankdir=LR;\n";
    for(auto entry: state_entry) {
        if(entry) {
            for(auto transition: entry->transition_list) {
                file << "    " << entry->tag << " -> " << state_entry[transition.state_id]->tag << " [label=\"" << transition.sym << "\"]\n";
            }
        }
    }
    file << "}\n";
}


void FA::printTable() {
    table.print();
}

void FA::printGraph(const char* file_stem) {
    std::ofstream dotfile(file_stem);
    table.printDot(dotfile);
    dotfile.close();

    char command[std::strlen(file_stem)*2+17];
    std::strcpy(command, "dot -Tpng ");
    std::strcpy(command+10, file_stem);
    std::strcpy(command+10+std::strlen(file_stem), " > ");
    std::strcpy(command+10+std::strlen(file_stem)+3, file_stem);
    std::strcpy(command+10+std::strlen(file_stem)+3+std::strlen(file_stem), ".png");
    std::system(command);
}

int FA::addTransition(int from, char sym, int to) {
    if(to == -1)
        to = ++state_id;
    table.addEntry(from, sym, to);
    return to;
}
