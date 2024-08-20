%{
#include <stdio.h>
#include "parser.h"

int line_number = 1;

%}

%option yylineno


BLOCK_COMMENT   "///".*"///"
LINE_COMMENT    "//"[^\/]+.*
INTEGER         [0-9]+
FLOAT           [0-9]+\.[0-9]+
IDENTIFIER      [a-z_][a-zA-Z0-9_]*
TYPE            [A-Z][a-zA-Z0-9_]*
STRING          \"([^\"\\]|\\.)*\"

%%

"let"                   {  return LET; }
"func"                  {  return FUNC; }
"object"                {  return OBJECT; }
"implements"            {  return IMPLEMENTS; }
"fields"                {  return FIELDS; }
"if"                    {  return IF; }
"for"                   {  return FOR; }
"break"                 {  return BREAK; }
"continue"              {  return CONTINUE; }
"return"                {  return RETURN; }
"import"                {  return IMPORT; }
"and"                   {  return AND; }
"or"                    {  return OR; }
"not"                   {  return NOT; }
"in"                    {  return IN; }

"("                     {  return LEFT_PAREN; }
")"                     {  return RIGHT_PAREN; }
"{"                     {  return LEFT_BRACE; }
"}"                     {  return RIGHT_BRACE; }
"["                     {  return LEFT_BRACKET; }
"]"                     {  return RIGHT_BRACKET; }
"<"                     {  return LEFT_ANGLE; }
">"                     {  return RIGHT_ANGLE; }
","                     {  return COMMA; }
"."                     {  return DOT; }
":"                     {  return COLON; }
"="                     {  return EQUAL; }
"-"                     {  return MINUS; }
"+"                     {  return PLUS; }
"*"                     {  return STAR; }
"/"                     {  return SLASH; }
"#"                     {  return HASH; }
"?"                     {  return QUEST_MARK; }
"!"                     {  return EXCLA_MARK; }
"%"                     {  return PERCENT; }
"$"                     {  return DOLLAR; }
"&"                     {  return AMPERSAND; }

"true"                  {  return BOOL; }
"false"                 {  return BOOL; }
{INTEGER}               { yylval.val = strdup(yytext);  return INTEGER; }
{FLOAT}                 { yylval.val = strdup(yytext);  return FLOAT; }
{IDENTIFIER}            { yylval.val = strdup(yytext);  return IDENTIFIER; }
{TYPE}                  { yylval.val = strdup(yytext);  return TYPE; }
{STRING}                { yylval.val = strdup(yytext);  return STRING; }

{BLOCK_COMMENT}         { printf("BLOCK_COMMENT\n"); /* Ignore line comment */ }
{LINE_COMMENT}          { printf("LINE_COMMENT\n"); /* Ignore line comment */ }
[ \t\n\r]+              { /* Ignore whitespace */ }

.                       { fprintf(stderr, "Unexpected character in line %d: %s\n", yylineno, yytext); exit(1); }

%%

int yywrap(void) {
    return 1;
}
