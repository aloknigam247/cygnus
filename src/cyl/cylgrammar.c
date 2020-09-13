#include "cylgrammar.h"
#include "genericlist.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct PattTagList* newPattTagList(const char *p, const char *t) {
    struct PattTagList *new_patt_tag = malloc(sizeof(struct PattTagList));
    new_patt_tag->patt = p ? strdup(p) : NULL ;
    new_patt_tag->tag = t ? strdup(t) : NULL;
    new_patt_tag->next = NULL;
    printf("new pattern tag unit: %s belongs %s\n", p, t);

    return new_patt_tag;
}

struct PattTagStmtList* newPattTagStmtList(const char* tag, struct PattTagList* tag_list) {
    struct PattTagStmtList *new_patt_stmt = malloc(sizeof(struct PattTagStmtList));
    new_patt_stmt->stmt_tag = tag ? strdup(tag) : NULL;
    new_patt_stmt->patt_tag_list = reverseGenericList(tag_list);
    new_patt_stmt->next = NULL;

    return new_patt_stmt;
}
