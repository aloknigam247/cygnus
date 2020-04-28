%define api.prefix {lang}
%code provides
{
  #define YY_DECL int langlex ()
  YY_DECL;
}
%{
#include <stdio.h>
extern FILE *langin;
%}
%token TYPE
%%
variable: TYPE
%%void langParse(FILE *file)
{
  // Set flex to read from it instead of defaulting to STDIN:
  langin = file;
  langparse();
}
langerror(char *s)
{
 printf("error: %s", s);
}
