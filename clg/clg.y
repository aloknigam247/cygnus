%{
#include <stdio.h>
#include "interface.h"

extern FILE *yyin;
char buff[1000];
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

filetype: FILETYPE COLON WS LOWER_WORD { setFileType($4); }

variable: UPPER_WORD WS PATTERN { insertVariable($1, $3); }

grammar: LOWER_WORD COLON WS UPPER_WORD { snprintf(buff, 1000, "%s%s%s%s", $1, $2, $3, $4); insertRule(buff); }
%%
void bisonParse(FILE *file)
{
  // Set flex to read from it instead of defaulting to STDIN:
  yyin = file;
  yyparse();
}
yyerror(char *s)
{
 printf("error: %s\n", s);
}
