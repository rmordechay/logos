%{
#include <stdio.h>
#include <stdlib.h>

extern int yylex();
extern int yyparse();
extern FILE* yyin;
void yyerror(const char* s);
#include "../ast/ast.h"
%}


%union {
    char* val;
    struct ASTNode *node;
}

%start program
%token LET FUNC OBJECT IMPORT LEFT_PAREN RIGHT_PAREN LEFT_BRACE RIGHT_BRACE LEFT_BRACKET RIGHT_BRACKET DOT COLON EQUAL MINUS PLUS STAR SLASH
%token <val> INTEGER FLOAT IDENTIFIER
%type <node> declaration unary_expr

%%


program:
      program declaration
    | declaration
    ;

declaration:
	unary_expr

unary_expr:
      INTEGER {  }
    | FLOAT {  }
    | IDENTIFIER {  }
    ;
%%

void yyerror(const char* s) {
    fprintf(stderr, "Parse error: %s\n", s);
    exit(1);
}