#ifdef EXTENDED_FEATURE
#include "status.h"
#include <string>
#include <map>
#include <vector>

struct LanguageBlock {
    std::vector<std::string> exts;
    std::string parent_pattern;
    std::vector<std::string> child_pattern;
    std::vector<std::map<int, std::string>> tag_pair_col;
};

class Cyl {
    public:
    Status readCyl(std::string lang_file);

    private:
    std::vector<LanguageBlock> lang_col;
};
#endif
