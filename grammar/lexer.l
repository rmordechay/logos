%{
#include <stdio.h>
#include "parser.h"
%}

%%

"let"                   { return LET; }
"("                     { return LEFT_PAREN; }
")"                     { return RIGHT_PAREN; }
"{"                     { return LEFT_BRACE; }
"{"                     { return RIGHT_BRACE; }
"["                     { return LEFT_BRACKET; }
"]"                     { return RIGHT_BRACKET; }
"."                     { return DOT; }
":"                     { return COLON; }
"="                     { return EQUAL; }
"-"                     { return MINUS; }
"+"                     { return PLUS; }
"*"                     { return STAR; }
"/"                     { return SLASH; }
[0-9]+                  { yylval.val = strdup(yytext); return INTEGER; }
[0-9]+\.[0-9]+          { yylval.val = strdup(yytext); return FLOAT; }
[a-zA-Z_][a-zA-Z0-9_]*  { yylval.val = strdup(yytext); return IDENTIFIER; }
.                       { printf("Unexpected character: %s\n", yytext); }

%%

int yywrap(void) {
    return 1;
}
