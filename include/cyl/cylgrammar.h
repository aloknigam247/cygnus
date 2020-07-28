#ifndef CYL_GRAMMAR_H
#define CYL_GRAMMAR_H

struct VariableList {
    char *id;
    char *pattern;
    struct VariableList *next;
};

struct RuleList {
    char *str;
    struct RuleList *next;
};

struct CylGrammar {
    char *file_type;
    struct VariableList *variable_head;
    struct VariableList *variable_tail;
    struct RuleList *rule_head;
    struct RuleList *rule_tail;
};

void insertRule(struct CylGrammar *digest, const char *rule);
void insertVariable(struct CylGrammar *digest, const char *var, const char *patt);
void setFileType(struct CylGrammar *digest, const char *file_type);

#endif
