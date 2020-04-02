%{
#include <stdio.h>
extern FILE *yyin;
%}
/* declare tokens */
%token COLON FILETYPE LOWER_WORD NL PATTERN UPPER_WORD WS
%%
stmt: filetype NL variable NL grammar NL

filetype: FILETYPE COLON WS LOWER_WORD

variable: UPPER_WORD WS PATTERN

grammar: LOWER_WORD COLON WS UPPER_WORD
%%
void callme(const *file)
{
  FILE *myfile = fopen(file, "r");
  // Set flex to read from it instead of defaulting to STDIN:
  yyin = myfile;
  yyparse();
}
yyerror(char *s)
{
 printf("error: %s\n", s);
}
