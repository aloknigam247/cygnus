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

#include "cylex.h"
#include "dfa.h"
#include "log.h"

void CyLex::addPattern(const char* patt) {
    lex_fa.addPattern(patt);
}

void CyLex::readFile(const char* file_name) {
    file.open(file_name);
}

 void CyLex::analyse() {
    std::string line, word;
    lex_fa.build();
    DFA dfa(lex_fa);
    while(std::getline(file, line)) {
        int b=0, e;
        for(int i = 0; i<line.size(); ++i) {
            if(line[i] == ' ') {
                e = i;
                std::string word = line.substr(b, e-b);
                if(dfa.execute(word.c_str())) {
                    std::cout << line << '\n';
                    break;
                }
                b = e+1;
            }
        }
        std::string word = line.substr(b);
        if(dfa.execute(word.c_str()))
            std::cout << line << '\n';
    }
}
