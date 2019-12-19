#include "cyfile.h"

#include <string>

#include "nfa.h"

class CyLex {
    public:
    void addPattern(const char* patt);
    void readFile(const char* file_name);
    void analyse();

    private:
    NFA lex_fa;
    CyFile file;
};
