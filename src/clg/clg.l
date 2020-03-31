/* even more like Unix wc */
%option noyywrap
%{
#include "clg.tab.h"
%}
%%
[A-Z]+ 	{printf("Identifier: %s\n", yytext);        return ID;}
[a-z]+  {printf("Rule: %s\n", yytext);              return RULE;}
\/.*\/  {printf("Pattern: %s\n", yytext);           return PATT;}
[ \t]+ 	{printf("Whitespace: \`%s\'\n", yytext);    return WS;}
'[a-z]' {printf("Literal: %s", yytext);             return LITERAL;}
; 		{printf("Semicolon: %s\n", yytext);         return SC;}
\| 		{printf("Pipe: %s\n", yytext);              return PIPE;}
: 		{printf("Colon: %s\n", yytext);             return COLON;}
[\n]    {printf("Newline:\n");                      return NL;}
. 	    {printf("Ignored: \`%s\'\n", yytext);}
%%
