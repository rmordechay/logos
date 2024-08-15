%{
#include <stdio.h>
#include <stdlib.h>
#include "ast/ast.h"
#include "utils/utils.h"

extern int yylex();
extern int yyparse();
extern int yylineno;
extern FILE* yyin;
void yyerror(const char* s);

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

%type <node> program object_file full_title primary_title secondary_title method_signature methods_block_list methods_block methods_list method param_list param fields_block field_list field variable_declaration identifier type type_list method_header

%%

program:
      	OBJECT COLON object_file { root = $3 }
    ;

object_file:
      	full_title fields_block methods_block_list { $$ = new_node(N_OBJECT_FILE, 3, $1, $2, $3) }
    | 	full_title fields_block { $$ = new_node(N_OBJECT_FILE, 2, $1, $2) }
    ;

full_title:
		primary_title secondary_title { $$ = new_node(N_FULL_TITLE, 2, $1, $2) }
	| 	primary_title { $$ = new_node(N_FULL_TITLE, 1, $1) }
	;

primary_title:
		identifier { $$ = new_node(N_PRIMARY_TITLE, 1, $1) }
	;

secondary_title:
		IMPLEMENTS COLON type_list { $$ = new_node(N_SECONDARY_TITLE, 1, $3) }
	;

fields_block:
      	FIELDS LEFT_BRACE field_list RIGHT_BRACE { $$ = new_node(N_FIELDS_BLOCK, 1, $3) }
    ;

field_list:
		field { $$ = new_node(N_FIELD_LIST, 1, $1) }
    | 	field_list field { $$ = flatten_list($1, $2) }
    ;

field:
    	variable_declaration  { $$ = new_node(N_FIELD, 2, $1);  }
    |	variable_declaration COLON type  { $$ = new_node(N_FIELD, 2, $1, $3);  }
    ;

methods_block_list:
		methods_block { $$ = new_node(N_METHODS_BLOCK_LIST, 1, $1) }
	|	methods_block_list methods_block { $$ = flatten_list($1, $2) }
	;

methods_block:
		identifier LEFT_BRACE methods_list RIGHT_BRACE { $$ = new_node(N_METHODS_BLOCK, 2, $1, $3) }
	;

methods_list:
		method { $$ = new_node(N_METHODS_LIST, 1, $1) }
	|	methods_list method { $$ = flatten_list($1, $2) }
	;

method:
		method_signature LEFT_BRACE RIGHT_BRACE { $$ = new_node(N_METHOD, 1, $1) }
	;

method_signature:
		method_header LEFT_PAREN param_list RIGHT_PAREN { $$ = new_node(N_METHOD_SIGNATURE, 2, $1, $3) }
	|	method_header LEFT_PAREN RIGHT_PAREN { $$ = new_node(N_METHOD_SIGNATURE, 1, $1) }
	;

method_header:
		FUNC variable_declaration { $$ = new_node(N_METHOD_HEADER, 1, $2) }
	;

param_list:
	   	param { $$ = new_node(N_PARAM_LIST, 1, $1) }
	 | 	param_list param { $$ = flatten_list($1, $2) }
	 ;

param:
		variable_declaration { $$ = new_node(N_PARAM, 1, $1) }
	;

variable_declaration:
		type identifier { $$ = new_node(N_VARIABLE_DECLARATION, 2, $1, $2) }
	;

identifier:
		IDENTIFIER { $$ = new_leaf(N_IDENTIFIER, yylval.val) }
	;

type:
    	IDENTIFIER { $$ = new_leaf(N_TYPE, yylval.val) }
    ;

type_list:
	  type { $$ = new_node(N_TYPE_LIST, 1, $1) }
	| type_list COMMA type { $$ = flatten_list($1, $3) }

%%

void yyerror(const char* s) {
    fprintf(stderr, "Parse error on line %d: %s\n", yylineno, s);
    exit(1);
}