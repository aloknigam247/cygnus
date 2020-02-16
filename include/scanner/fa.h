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

#ifndef SCANNER_FA_H
#define SCANNER_FA_H

#include <fstream>
#include <list>
#include <string>
#include <vector>

#include "log.h"

struct StateEntry {
    struct Transition {
        char sym;
        int state_id;
    };

    std::string tag = "q";
    bool is_final = false;
    std::list<Transition> transition_list;
    StateEntry(): transition_list(0) {}
};

class StateTable {
    const int MAX_ENTRY = 100;

    public:
    StateTable(): state_entry(MAX_ENTRY, nullptr) {}
    ~StateTable();
    void addEntry(int from, char sym, int to);
    void print() const;
    void printDot(std::ofstream& file) const;
    void set_final(int i) { state_entry[i]->is_final = true; }
    StateEntry* get_entry(int i) { return state_entry[i]; }

    private:
    std::vector<StateEntry*> state_entry;
};

class FA {
    public:
    void printTable() const;
    void printGraph(const char* file_stem = "fa") const;

    protected:
    int addTransition(int from, char sym, int to=-1);
    int addTransition(const std::vector<int>& from, char sym, int to=-1);
    StateTable get_table() { return table; }

    private:
    StateTable table;
    int state_id = 0;
};

#endif
