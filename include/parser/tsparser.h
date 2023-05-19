#include "parser.h"

// FIX: Change TsParser class name as it conflicts with TreeSitter name
class TsParser: public Parser<void> {
    public:
    void parse(std::string file) override;
};
