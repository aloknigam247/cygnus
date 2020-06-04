#include <string>

struct Grammar;

class Parser {
    public:
    virtual Grammar* parse(std::string file) = 0;
};

class BisonParser: public Parser {
    Grammar* parse(std::string file) override;
};

#ifdef EXTENDED_FEATURE
class CyParser: public Parser {
    Grammar* parse(std::string file) override;
};
#endif

enum class ParserType {
    Bison,
    CyParser
};

Parser *parserFactory(ParserType t);
