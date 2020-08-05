#ifdef EXTENDED_FEATURE
#include "cylgrammar.h"

#include <string>
#include "cyfile.h"

class Writer {
    public:
    virtual void write(CylGrammar *g, std::string file) = 0;
};

class BisonWriter: public Writer {
    public:
    virtual void write(CylGrammar *g, std::string file) override;
};

class FlexWriter: public Writer {
    public:
    virtual void write(CylGrammar *g, std::string file) override;
};

class CyParseWriter: public Writer {
    public:
    virtual void write(CylGrammar *g, std::string file) override;
};

class CyLexWriter: public Writer {
    public:
    virtual void write(CylGrammar *g, std::string file) override;
};

enum class WriterType {
    Bison,
    CyLex,
    CyParse,
    Flex
};

Writer* writerFactory(WriterType type); // TODO: can any other design pattern work here
#endif
