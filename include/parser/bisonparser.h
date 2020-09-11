#ifdef EXTENDED_FEATURE
#include "parser.h"
#include "bisondigest.h"

class BisonParser: public Parser<BisonDigest*> {
    public:
    BisonDigest* parse(std::string file) override;
};
#endif
