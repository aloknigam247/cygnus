%define api.prefix {cyl}

%{
#include <stdio.h>
#include "cylgrammar.h"

extern FILE *yyin;
char buff[1000];
%}

%parse-param {struct CylGrammar *digest}

%union {
    char* str;
    struct PattTagList* pattTagPtr;
    struct PattTagStmtList* pattStmtPtr;
}

/* declare tokens */
%token <str> COLON
%token <str> EXTENSION
%token <str> LOWER_WORD
%token <str> NL
%token <str> PATTERN
%token <str> UPPER_WORD
%token <str> WS

%%
stmt: extension NL patt_block NL

extension: EXTENSION COLON WS LOWER_WORD { digest->ext = strdup($4); }

patt_block: patt_stmt { digest->patt_stmt_head = $<pattStmtPtr>1; }
          | patt_block NL patt_stmt { digest->patt_stmt_head = $<pattStmtPtr>1; $<pattStmtPtr>1->next = $<pattStmtPtr>3; }

patt_stmt: LOWER_WORD COLON WS patt_tag { $<pattStmtPtr>$ = newPattTagStmtList($1, $<pattTagPtr>4); }

patt_tag: patt_tag_unit             { $<pattTagPtr>$ = $<pattTagPtr>1; }
        | patt_tag WS patt_tag_unit { $<pattTagPtr>3->next = $<pattTagPtr>1 ; $<pattTagPtr>$ = $<pattTagPtr>3; }

patt_tag_unit: PATTERN            { $<pattTagPtr>$ = newPattTagList($1, NULL); }
             | PATTERN LOWER_WORD { $<pattTagPtr>$ = newPattTagList($1, $2); }
%%
void* CylBisonEntry(const char *file_name) {
    FILE *file = fopen(file_name, "r");
    if(file == NULL)
        return NULL;

    yyin = file;
    struct CylGrammar *digest = malloc(sizeof(struct CylGrammar));
    cylparse(digest);

    fclose(file);
    return digest;
}

void cylerror(char *s) {
    printf("error: %s\n", s);
}
