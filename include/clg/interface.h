#ifndef INTERFACE_H
#define INTERFACE_H

struct VariableList {
    char *id;
    char *pattern;
    struct VariableList *next;
};

struct RuleList {
    char *str;
    struct RuleList *next;
};

struct Grammar {
    char *file_type;
    struct VariableList *variable_head;
    struct VariableList *variable_tail;
    struct RuleList *rule_head;
    struct RuleList *rule_tail;
};

extern struct Grammar instr_digest;

struct Grammar *digest(const char *file_name);
void insertRule(const char *rule);
void insertVariable(const char *var, const char *patt);
void setFileType(const char *file_type);

#endif
