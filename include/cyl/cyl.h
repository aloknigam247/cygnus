#ifndef CYL_H
#define CYL_H
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

using LangBlockColl = std::map<std::string, LangBlock>;

class Cyl {
    public:
    Status readCyl(std::string lang_file);
    LangBlock getLangBlock(std::string filetype);
    std::vector<std::string> filetypes();
    std::vector<std::string> fileExts(std::string filetype) { return {filetype}; }

    private:
    LangBlockColl lang_coll;
};
#endif
