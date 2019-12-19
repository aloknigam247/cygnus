#include "cylex.h"

#include "log.h"

void CyLex::addPattern(const char* patt) {
    lex_fa.addPattern(patt);
}

void CyLex::readFile(const char* file_name) {
    file.open(file_name);
}

void CyLex::analyse() {
    std::string word;
    lex_fa.compile();
    while(file >> word) {
        Log::d("word: ", word);
        if(lex_fa.execute(word.c_str()))
            Log::d("M");
        else
            Log::d("U");
    }
}
