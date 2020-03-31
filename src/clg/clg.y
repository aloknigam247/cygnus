/* simplest version of calculator */
%{
#include <stdio.h>
extern FILE *yyin;
%}
/* declare tokens */
%token ID WS PATT SC NL RULE LITERAL COLON PIPE
%%
stmt: {printf("Variables -->>\n");} variable_rule {printf("Variables Done\n\n");} NL {printf("Grammar -->>\n");} grammar_rule {printf("Compilation Done\n");} NL

variable_rule: /* nothing */ {printf("Empty Variable\n");}
    | ID WS PATT NL variable_rule {printf("Variable Decleration\n");}

grammar_rule: /* nothing */ {printf("Empty grammar\n");}
    | RULE COLON WS grammar_element {printf("Grammar Decleration\n");}

grammar_element: 
    | RULE | ID | LITERAL | PIPE
    | grammar_element WS grammar_element
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
