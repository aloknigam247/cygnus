#ifdef EXTENDED_FEATURE
#include "parser.h"

class BisonParser: public Parser {
    public:
    Digest* parse(std::string file) override;
    void set_entry(void* (*p)(const char*)) { bison_entry = p; }

    private:
    void* (*bison_entry)(const char*);
};
#endif
