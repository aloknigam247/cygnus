/* even more like Unix wc */
%option noyywrap
%{
#include "clg-bison.h"
%}
%%
: 		    { printf("COLON: %s\n", yytext);            return COLON; }
filetype    { printf("FILETYPE: %s\n", yytext);         return FILETYPE; }
[a-z]+      { printf("LOWER_WORD: %s\n", yytext);       return LOWER_WORD; }
[\n]        { printf("NL:\n");                          return NL; }
\/.*\/      { printf("PATTERN: %s\n", yytext);          return PATTERN; }
[A-Z]+      { printf("UPPER_WORD: %s\n", yytext);       return UPPER_WORD; }
[ \t] 	    { printf("Whitespace: \`%s\'\n", yytext);   return WS; }
. 	        { printf("ignored: \`%s\'\n", yytext); }
%%
