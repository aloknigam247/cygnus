/* even more like Unix wc */
%option noyywrap
%{
#include "clg.tab.h"
%}
%%
[a-z]+ 		{printf("Identifier: %s\n", yytext); return ID;}
\/[a-z]+\/ 	{printf("Pattern: %s\n", yytext); return PATT;}
[ \t]+ 		{printf("Whitespace: \`%s\'\n", yytext); return WS;}
; 			{printf("Semicolon: %s\n", yytext); return SC;}
\n 			{printf("Newline:\n"); return NL;}
. 			{printf("Ignored: \`%s\'\n", yytext);}
%%
