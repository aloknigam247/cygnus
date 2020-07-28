%{
#include <stdio.h>
#include "cylgrammar.h"

extern FILE *yyin;
char buff[1000];

struct CylGrammar *digest = NULL;
%}

%union {
    char* str;
}
/* declare tokens */
%token <str> COLON
%token <str> FILETYPE
%token <str> LOWER_WORD
%token <str> NL
%token <str> PATTERN
%token <str> UPPER_WORD
%token <str> WS

%%
stmt: filetype NL variable NL grammar NL

filetype: FILETYPE COLON WS LOWER_WORD { setFileType(digest, $4); }

variable: UPPER_WORD WS PATTERN { insertVariable(digest, $1, $3); }

grammar: LOWER_WORD COLON WS UPPER_WORD { snprintf(buff, 1000, "%s%s%s%s", $1, $2, $3, $4); insertRule(digest, buff); }

%%
void* CylBisonEntry(const char *file_name) {
    FILE *file = fopen(file_name, "r");
    if(file == NULL)
        return NULL;

    yyin = file;
    digest = malloc(sizeof(struct CylGrammar));
    yyparse();

    fclose(file);
    return digest;
}

yyerror(char *s) {
    printf("error: %s\n", s);
}
