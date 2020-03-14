/* simplest version of calculator */
%{
#include <stdio.h>
extern FILE *yyin;
%}
/* declare tokens */
%token ID WS PATT SC NL
%%
S: /* nothing */ {printf("EMPTY\n");}
 | S NL S
 | ID WS PATT SC {printf("Statement\n");}
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
 fprintf(stderr, "error: %s\n", s);
}
