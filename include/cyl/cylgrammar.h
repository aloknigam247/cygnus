#ifndef CYL_GRAMMAR_H
#define CYL_GRAMMAR_H

struct PattTagList {
    struct PattTagList *next;
    char *patt;
    char *tag;
};

struct PattTagStmtList {
    struct PattTagStmtList* next;
    char *stmt_tag;
    struct PattTagList* patt_tag_list;
};

struct VariableList {
    struct VariableList *next;
    char *id;
    char *pattern;
};

struct RuleList {
    struct RuleList *next;
    char *str;
};

struct CylGrammar {
    char *ext;
    struct PattTagStmtList *patt_stmt_head;
    struct RuleList *rule_head;
    struct RuleList *rule_tail;
    struct VariableList *variable_head;
    struct VariableList *variable_tail;
};

struct PattTagList* newPattTagList(const char *p, const char *t);
struct PattTagStmtList* newPattTagStmtList(const char* tag, struct PattTagList* tag_list);
void setFileType(struct CylGrammar *digest, const char *file_type);

#endif
