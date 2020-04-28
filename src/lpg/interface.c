#include "interface.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void bisonParse(FILE *file);

struct Grammar instr_digest = {NULL};

struct Grammar *digest(const char *file_name) {
    FILE *file = fopen(file_name, "r");
    if(file == NULL)
        return NULL;

//    bisonParse(file);

    fclose(file);

    return &instr_digest;
}

void insertRule(const char *rule) {
    struct RuleList *new = malloc(sizeof(struct RuleList));
    new->str = strdup(rule);
    new->next = NULL;

    if(instr_digest.rule_tail == NULL)
        instr_digest.rule_head = new;
    else
        instr_digest.rule_tail->next = new;

    instr_digest.rule_tail = new;

    printf("new rule: %s\n", rule);
}

void insertVariable(const char *var, const char *patt) {
    struct VariableList *new = malloc(sizeof(struct VariableList));
    new->id = strdup(var);
    new->pattern = strdup(patt);
    new->next = NULL;

    if(instr_digest.variable_tail == NULL)
        instr_digest.variable_head = new;
    else
        instr_digest.variable_tail->next = new;

    instr_digest.variable_tail = new;

    printf("new variable: %s = %s\n", var, patt);
}

void setFileType(const char *file_type) {
    instr_digest.file_type = strdup(file_type);
    printf("filetype set: %s\n", file_type);
}
