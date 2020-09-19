%option noyywrap
%{
#define YY_DECL int cyllex (void)
#include "cyl-bison.h"
%}
%%
:          { printf("flex::COLON: %s\n", yytext);          cyllval.str = strdup(yytext); return COLON; }
Extension  { printf("flex::EXTENSION: %s\n", yytext);      cyllval.str = strdup(yytext); return EXTENSION; }
[a-z]+     { printf("flex::LOWER_WORD: %s\n", yytext);     cyllval.str = strdup(yytext); return LOWER_WORD; }
[\n]       { printf("flex::NL\n");                         cyllval.str = strdup(yytext); return NL; }
%[^%]*%  { printf("flex::PATTERN: %s\n", yytext);        cyllval.str = strdup(yytext); return PATTERN; }
[A-Z]+     { printf("flex::UPPER_WORD: %s\n", yytext);     cyllval.str = strdup(yytext); return UPPER_WORD; }
[ \t]      { printf("flex::Whitespace: \'%s\'\n", yytext); cyllval.str = strdup(yytext); return WS; }
.          { printf("flex::ignored: \'%s\'\n", yytext); }
%%
