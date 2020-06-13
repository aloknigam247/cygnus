#include <string>

class Digest {
    public:
    void set_data(void* d) { data = d; }
    void* get_data() { return data; }

    private:
    void *data;
};

class Parser {
    public:
    virtual Digest* parse(std::string file) = 0;
};

class BisonParser: public Parser {
    public:
    Digest* parse(std::string file) override;
    void set_entry(void* (*p)(const char*)) { bison_entry = p; }

    private:
    void* (*bison_entry)(const char*);

};

#ifdef EXTENDED_FEATURE
class CyParser: public Parser {
    public:
    Digest* parse(std::string file) override;
};
#endif

enum class ParserType {
    Bison,
    CyParser
};

Parser *parserFactory(ParserType t);
