#include <string>

class Parser {
    public:
    virtual void parse(std::string file) = 0;
};

class BisonParser: public Parser {
    void parse(std::string file) override;
};

#ifdef EXTENDED_FEATURE
class CyParser: public Parser {
    void parse(std::string file) override;
};
#endif

class ParserFactory: public Parser {
};

enum class ParserType {
    Bison,
    CyParser
};

Parser *parserFactory(ParserType t);
