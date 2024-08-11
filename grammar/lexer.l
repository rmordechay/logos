%{
#include <stdio.h>
#include "parser.h"
%}

%%

"let"                   { yylval.val = strdup(yytext); return LET; }
"func"                  { yylval.val = strdup(yytext); return FUNC; }
"object"                { yylval.val = strdup(yytext); return OBJECT; }
"("                     { yylval.val = strdup(yytext); return LEFT_PAREN; }
")"                     { yylval.val = strdup(yytext); return RIGHT_PAREN; }
"{"                     { yylval.val = strdup(yytext); return LEFT_BRACE; }
"{"                     { yylval.val = strdup(yytext); return RIGHT_BRACE; }
"["                     { yylval.val = strdup(yytext); return LEFT_BRACK; }
"]"                     { yylval.val = strdup(yytext); return RIGHT_BRACK; }
":"                     { yylval.val = strdup(yytext); return COLON; }
[0-9]+                  { yylval.val = strdup(yytext); return INTEGER; }
[0-9]+\.[0-9]+          { yylval.val = strdup(yytext); return FLOAT; }
[a-zA-Z_][a-zA-Z0-9_]*  { yylval.val = strdup(yytext); return IDENTIFIER; }
.                       { printf("Unexpected character: %s\n", yytext); }

%%

int yywrap(void) {
    return 1;
}
