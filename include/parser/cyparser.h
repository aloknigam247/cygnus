#ifdef EXTENDED_FEATURE
#include "parser.h"

class CyParser: public Parser {
    public:
    Digest* parse(std::string file) override;
};
#endif
