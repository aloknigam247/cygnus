#include "writer.h"

Writer* writerFactory(WriterType type) { // TODO: can any other design pattern work here
    Writer *w;
    switch(type) {
        case WriterType::Bison:
            w = new BisonWriter;
            break;
#ifdef EXTENDED_FEATURE
        case WriterType::CyLex:
            w = new CyLexWriter;
            break;
        case WriterType::CyParse:
            w = new CyParseWriter;
            break;
#endif
        case WriterType::Flex:
            w = new FlexWriter;
            break;
    }
    return w;
}

void BisonWriter::write() {
}

/*
void LPG::generateBison(Grammar *g, std::string file_base) {
    CyFile bison;
    bison.open(file_base + ".y", std::ios::out);

    bison << "%define api.prefix {lang}\n";
    bison << "%code provides\n";
    bison << "{\n";
    bison << "  #define YY_DECL int langlex ()\n";
    bison << "  YY_DECL;\n";
    bison << "}\n";
    bison << "%{\n";
    bison << "#include <stdio.h>\n";
    bison << "extern FILE *langin;\n";
    bison << "%}\n";

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
    bison << "void langParse(FILE *file)\n";
    bison << "{\n";
    bison << "  // Set flex to read from it instead of defaulting to STDIN:\n";
    bison << "  langin = file;\n";
    bison << "  langparse();\n";
    bison << "}\n";
    bison << "langerror(char *s)\n";
    bison << "{\n";
    bison << " printf(\"error: %s\", s);\n";
    bison << "}\n";
    bison.close();
}
*/
void FlexWriter::write() {
}

/*
void LPG::generateFlex(VariableList *variable_list, std::string file_base, std::string file_stem) {
    if(!variable_list)
        return;

    CyFile flex;
    flex.open(file_base + ".l", std::ios::out);

    flex << "%{\n";
    flex << "#include \"" << file_stem << "-bison.h\"\n";
    flex << "%}\n";
    flex << "%%\n";
    while(variable_list) {
        std::string tmp = variable_list->pattern;
        tmp.erase(0,1);
        tmp.erase(tmp.size()-1, 1);
        flex << tmp << " { return " << variable_list->id << "; }\n";
        variable_list = variable_list->next;;
    }
    flex << "%%";
}*/
