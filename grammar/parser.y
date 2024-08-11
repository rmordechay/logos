%{
#include <stdio.h>
#include <stdlib.h>

extern int yylex();
extern int yyparse();
extern FILE* yyin;

void yyerror(const char* s);
%}

%union {
    char* val;
}

%token <val> OBJECT
%token <val> FUNC
%token <val> LET
%token <val> INTEGER
%token <val> FLOAT
%token <val> IDENTIFIER
%token <val> COLON
%token <val> LEFT_PAREN
%token <val> RIGHT_PAREN
%token <val> LEFT_BRACE
%token <val> RIGHT_BRACE
%token <val> LEFT_BRACK
%token <val> RIGHT_BRACK

%%

program:
      program declaration
    | declaration
    ;

declaration:
	unary_expr

unary_expr:
      INTEGER { }
    | FLOAT { }
    | IDENTIFIER { }
    ;
%%

void yyerror(const char* s) {
    fprintf(stderr, "Parse error: %s\n", s);
    exit(1);
}