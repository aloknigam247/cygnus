/************************************************************************************
 * MIT License                                                                      *
 *                                                                                  *
 * Copyright (c) 2019 Alok Nigam                                                    *
 *                                                                                  *
 * Permission is hereby granted, free of charge, to any person obtaining a copy     *
 * of this software and associated documentation files (the "Software"), to deal    *
 * in the Software without restriction, including without limitation the rights     *
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell        *
 * copies of the Software, and to permit persons to whom the Software is            *
 * furnished to do so, subject to the following conditions:                         *
 *                                                                                  *
 * The above copyright notice and this permission notice shall be included in all   *
 * copies or substantial portions of the Software.                                  *
 *                                                                                  *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR       *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,         *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE      *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER           *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,    *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE    *
 * SOFTWARE.                                                                        *
 ************************************************************************************/

#include "fa.h"

#include <cstdlib>
#include <cstring>
#include <iostream>

void StateTable::addEntry(int from, char sym, int to) {
    if(state_entry[from] == nullptr)
        state_entry[from] = new StateEntry;

    if(state_entry[from]->tag.size() == 1)
        state_entry[from]->tag += std::to_string(from);

    state_entry[from]->transition_list.push_back(StateEntry::Transition{sym, to});

    if(state_entry[to] == nullptr) {
        state_entry[to] = new StateEntry;
        state_entry[to]->tag += std::to_string(to);
    }
}

void StateTable::print() const {
    std::cout << "index\ttag\tfinal\t(sym,to)...\n";
    for(std::size_t i=0; i<state_entry.size(); ++i) {
        if(state_entry[i] != nullptr) {
            StateEntry* entry = state_entry[i];
            std::cout << i << '\t';
            std::cout << entry->tag << '\t' << entry->is_final << '\t';
            for(auto transition: entry->transition_list) {
                std::cout << '(' <<transition.sym << ',' << transition.state_id << ')' << '\t';
            }
            std::cout << "\n";
        }
    }
}

void StateTable::printDot(std::ofstream& file) const {
    file << "digraph fa {\n"
        << "    rankdir=LR;\n";
    for(auto entry: state_entry) {
        if(entry != nullptr) {
            for(auto transition: entry->transition_list) {
                file << "    {";
                if(entry->is_final)
                    file << "node [shape=doublecircle] ";
                file << entry->tag << "} -> {";
                if(state_entry[transition.state_id]->is_final)
                    file << "node [shape=doublecircle] ";
                file << state_entry[transition.state_id]->tag << "} [label=\"" << transition.sym << "\"]\n";
            }
        }
    }
    file << "}\n";
}


void FA::printTable() const {
    table.print();
}

void FA::printGraph(const char* file_stem) const {
    std::ofstream dotfile(file_stem);
    table.printDot(dotfile);
    dotfile.close();

    std::string command;

    command = "dot -Tpng ";
    command += file_stem;
    command += " > ";
    command += file_stem;
    command += ".png";
    std::system(command.c_str());
}

int FA::addTransition(int from, char sym, int to) {
    if(to == -1)
        to = ++state_id;
    table.addEntry(from, sym, to);
    return to;
}

int FA::addTransition(const std::vector<int>& from, char sym, int to) {
    if(to == -1)
        to = ++state_id;
    for(auto f: from)
        table.addEntry(f, sym, to);
    return to;
}
