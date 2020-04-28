#include <string>

extern "C" {
#include "interface.h"
}

class CLG {
    public:
    int parse(std::string lang_file);

    private:
    void generateParser(Grammar *g, std::string lang_file);
    void generateBison(Grammar *g, std::string file_base);
    void generateFlex(VariableList *variable_list, std::string file_base, std::string file_stem);
};
