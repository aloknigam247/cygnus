class Writer {
    public:
    virtual void write() = 0;
};

class BisonWriter: public Writer {
    public:
    virtual void write() override;
};

class FlexWriter: public Writer {
    public:
    virtual void write() override;
};

#ifdef EXTENDED_FEATURE
class CyParseWriter: public Writer {
    public:
    virtual void write() override;
};

class CyLexWriter: public Writer {
    public:
    virtual void write() override;
};
#endif

enum class WriterType {
    Bison,
    CyLex,
    CyParse,
    Flex
};

Writer* writerFactory(WriterType type); // TODO: can any other design pattern work here
