%{
#include <stdio.h>
#include "parser.h"

int line_number = 1;
%}

%option yylineno

%%

"let"                   { return LET; }
"func"                  { return FUNC; }
"object"                { return OBJECT; }
"implements"            { return IMPLEMENTS; }
"fields"                { return FIELDS; }

"("                     { return LEFT_PAREN; }
")"                     { return RIGHT_PAREN; }
"{"                     { return LEFT_BRACE; }
"}"                     { return RIGHT_BRACE; }
"["                     { return LEFT_BRACKET; }
"]"                     { return RIGHT_BRACKET; }
","                     { return COMMA; }
"."                     { return DOT; }
":"                     { return COLON; }
"="                     { return EQUAL; }
"-"                     { return MINUS; }
"+"                     { return PLUS; }
"*"                     { return STAR; }
"/"                     { return SLASH; }
"#"                     { return HASH; }
"?"                     { return QUEST_MARK; }
"!"                     { return EXCLA_MARK; }
"%"                     { return PERCENT; }
"$"                     { return DOLLAR; }
"&"                     { return AMPERSAND; }

[0-9]+                  { yylval.val = strdup(yytext); return INTEGER; }
[0-9]+\.[0-9]+          { yylval.val = strdup(yytext); return FLOAT; }
[a-zA-Z_][a-zA-Z0-9_]*  { yylval.val = strdup(yytext); return IDENTIFIER; }

[ \n\t]+                  { /* Ignore whitespace */ }

.                       { printf("(%d) Unexpected character: %s\n", yylineno, yytext); }

%%

int yywrap(void) {
    return 1;
}
