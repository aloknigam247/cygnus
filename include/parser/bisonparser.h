#ifdef EXTENDED_FEATURE
#include "parser.h"

class BisonParser: public Parser {
    public:
    Digest* parse(std::string file) override;
};
#endif
