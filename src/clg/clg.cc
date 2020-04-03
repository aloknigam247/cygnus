#include "clg.h"
#include "log.h"
#include "cyfile.h"

int CLG::parse(std::string lang_file) {
    struct Grammar *g = digest(lang_file.c_str());
    generateParser(g, lang_file);
    return 0;
}

void CLG::generateParser(Grammar *g, std::string lang_file) {
    if(!g)
        return;

    std::string file_stem = lang_file.substr(0, lang_file.size()-4);
    generateBison(g, file_stem);
    generateFlex(g->variable_head, file_stem);
}

void CLG::generateBison(Grammar *g, std::string file_stem) {
    CyFile bison;
    bison.open(file_stem + ".y", std::ios::out);

    if(g->variable_head) {
        VariableList *curr_var = g->variable_head;
        bison << "%token";
        while(curr_var) {
            bison << ' ' << curr_var->id;
            curr_var = curr_var->next;
        }
        bison << '\n';
    }

    bison << "%%\n";

    if(g->rule_head) {
        RuleList *curr_rule = g->rule_head;
        while(curr_rule) {
            bison << curr_rule->str << '\n';
            curr_rule = curr_rule->next;
        }
    }

    bison << "%%";
    bison.close();
}

void CLG::generateFlex(VariableList *variable_list, std::string file_stem) {
    if(!variable_list)
        return;

    CyFile flex;
    flex.open(file_stem + ".l", std::ios::out);

    flex << "%%\n";
    while(variable_list) {
        flex << variable_list->pattern << " { return " << variable_list->id << " }\n";
        variable_list = variable_list->next;;
    }
    flex << "%%";
}
