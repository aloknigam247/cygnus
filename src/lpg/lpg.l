%option noyywrap
%{
#include "lpg-bison.h"
%}
%%
: 		    { printf("flex::COLON: %s\n", yytext);            yylval.str = strdup(yytext); return COLON; }
filetype    { printf("flex::FILETYPE: %s\n", yytext);         yylval.str = strdup(yytext); return FILETYPE; }
[a-z]+      { printf("flex::LOWER_WORD: %s\n", yytext);       yylval.str = strdup(yytext); return LOWER_WORD; }
[\n]        { printf("flex::NL\n");                           yylval.str = strdup(yytext); return NL; }
\/.*\/      { printf("flex::PATTERN: %s\n", yytext);          yylval.str = strdup(yytext); return PATTERN; }
[A-Z]+      { printf("flex::UPPER_WORD: %s\n", yytext);       yylval.str = strdup(yytext); return UPPER_WORD; }
[ \t] 	    { printf("flex::Whitespace: \`%s\'\n", yytext);   yylval.str = strdup(yytext); return WS; }
. 	        { printf("flex::ignored: \`%s\'\n", yytext); }
%%
