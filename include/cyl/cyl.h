#ifndef CYL_H
#define CYL_H
#ifdef EXTENDED_FEATURE
#include "status.h"
#include <string>
#include <map>
#include <vector>

struct LangBlock {
    std::vector<std::string> exts;
    std::string parent_pattern;
    std::vector<std::string> child_pattern;
    std::vector<std::map<int, std::string>> tag_pair_col;
};

using LangBlockCol = std::vector<LangBlock>;

class Cyl {
    public:
    Status readCyl(std::string lang_file);
    LangBlockCol getLangBlock() { return lang_col; }

    private:
    LangBlockCol lang_col;
};
#endif
#endif
