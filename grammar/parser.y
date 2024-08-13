%{
#include <stdio.h>
#include <stdlib.h>

extern int yylex();
extern int yyparse();
extern int yylineno;
extern FILE* yyin;
void yyerror(const char* s);
#include "../ast/ast.h"

struct ASTNode *root;

%}


%union {
    char* val;
    struct ASTNode *node;
}

%start program

%token LET FUNC IMPLEMENTS FIELDS SELF OBJECT
%token LEFT_PAREN RIGHT_PAREN LEFT_BRACE RIGHT_BRACE LEFT_BRACKET RIGHT_BRACKET
%token COMMA DOT COLON EQUAL MINUS PLUS STAR SLASH HASH QUEST_MARK EXCLA_MARK PERCENT DOLLAR AMPERSAND
%token <val> INTEGER FLOAT IDENTIFIER

%type <node> program object_file title primary_title secondary_title methods_block_list methods_block methods_list method param_list param full_variable_declaration fields_block field_list field variable_declaration identifier type

%%

program:
      	object_file { root = $$ }
    ;

object_file:
      	title fields_block methods_block_list { $$ = new_node(N_OBJECT_FILE, 3, $1, $2, $3) }
    | 	title fields_block { $$ = new_node(N_OBJECT_FILE, 2, $1, $2) }
    ;

title:
		primary_title secondary_title { $$ = new_node(N_TITLE, 2, $1, $2) }
	| 	primary_title { $$ = new_node(N_TITLE, 2, $1) }
	;

primary_title:
		OBJECT COLON identifier { $$ = new_node(N_PRIMARY_TITLE, 1, $3) }
	;

secondary_title:
		IMPLEMENTS COLON identifier { $$ = new_node(N_SECONDARY_TITLE, 1, $3) }
	;

methods_block_list:
		methods_block { $$ = new_node(N_METHODS_BLOCK_LIST, 1, $1) }
	|	methods_block_list methods_block { $$ = new_node(N_METHODS_BLOCK_LIST, 1, $2) }
	;

methods_block:
		FIELDS LEFT_BRACE methods_list RIGHT_BRACE { $$ = new_node(N_METHODS_BLOCK, 1, $3) }
	;

methods_list:
		method { $$ = new_node(N_METHODS_LIST, 1, $1) }
	|	methods_list method { $$ = new_node(N_METHODS_LIST, 1, $2) }
	;

method:
		FUNC identifier LEFT_PAREN param_list RIGHT_PAREN LEFT_BRACE RIGHT_BRACE { $$ = new_node(N_METHOD, 2, $2, $4) }
	;

param_list:
	   	param { $$ = new_node(N_PARAM_LIST, 1, $1) }
	 | 	param_list param { $$ = new_node(N_PARAM_LIST, 1, $2) }
	 ;

param:
		variable_declaration { $$ = new_node(N_PARAM, 1, $1) }
	|	param COMMA variable_declaration { $$ = new_node(N_PARAM, 2, $1, $3) }
	;

fields_block:
      	FIELDS LEFT_BRACE field_list RIGHT_BRACE { $$ = new_node(N_FIELDS_BLOCK, 1, $3) }
    ;

field_list:
		field { $$ = new_node(N_FIELD_LIST, 1, $1) }
    | 	field_list field { $$ = new_node(N_FIELD_LIST, 1, $2) }
    ;

field:
    	type full_variable_declaration { $$ = new_node(N_FIELD, 3, $1, $2);  }
    ;

full_variable_declaration:
		identifier COLON type { $$ = new_node(N_FULL_VARIABLE_DECLARATION, 2, $1, $3) }
	;

variable_declaration:
		full_variable_declaration { $$ = new_node(N_VARIABLE_DECLARATION, 1, $1) }
	|	identifier { $$ = new_node(N_VARIABLE_DECLARATION, 1, $1) }
	;

identifier:
		IDENTIFIER { $$ = new_leaf(N_IDENTIFIER, yylval.val) }
	;

type:
    	IDENTIFIER { $$ = new_leaf(N_TYPE, yylval.val) }
    ;

%%

void yyerror(const char* s) {
    fprintf(stderr, "Parse error on line %d: %s\n", yylineno, s);
    exit(1);
}