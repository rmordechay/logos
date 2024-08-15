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

struct Node *root;
%}



%union {
    char* val;
    struct Node *node;
}

%start program

%token LET FUNC IMPLEMENTS FIELDS SELF OBJECT
%token LEFT_PAREN RIGHT_PAREN LEFT_BRACE RIGHT_BRACE LEFT_BRACKET RIGHT_BRACKET
%token COMMA DOT COLON EQUAL MINUS PLUS STAR SLASH HASH QUEST_MARK EXCLA_MARK PERCENT DOLLAR AMPERSAND
%token <val> INTEGER FLOAT IDENTIFIER

%type <node> program object_file full_title primary_title secondary_title fields_block field_list field methods_block_list methods_block methods_list method method_signature method_header statement_list statement expr unary_expr add_expr sub_expr mul_expr div_expr local_declaration variable_declaration variable_declaration_list identifier type type_list

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
    	variable_declaration  { $$ = new_node(N_FIELD, 1, $1)  }
    |	variable_declaration COLON type  { $$ = new_node(N_FIELD, 2, $1, $3)  }
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
		method_signature LEFT_BRACE statement_list RIGHT_BRACE { $$ = new_node(N_METHOD, 1, $1) }
	;

method_signature:
		method_header LEFT_PAREN variable_declaration_list RIGHT_PAREN { $$ = new_node(N_METHOD_SIGNATURE, 2, $1, $3) }
	|	method_header LEFT_PAREN RIGHT_PAREN { $$ = new_node(N_METHOD_SIGNATURE, 1, $1) }
	;

method_header:
		FUNC variable_declaration { $$ = new_node(N_METHOD_HEADER, 1, $2) }
	;


statement_list:
		/* empty */
	|	statement { $$ = new_node(N_STATEMENT_LIST, 1, $1) }
	|	statement_list statement { $$ = flatten_list($1, $2) }
	;

statement:
		local_declaration
	;

local_declaration:
		LET variable_declaration EQUAL expr { $$ = new_node(N_LOCAL_DECLARATION, 2, $2, $4) }
	;

expr:
		unary_expr { $$ = new_node(N_EXPR, 1, $1) }
	|	add_expr { $$ = new_node(N_EXPR, 1, $1) }
	|	sub_expr { $$ = new_node(N_EXPR, 1, $1) }
	|	mul_expr { $$ = new_node(N_EXPR, 1, $1) }
	|	div_expr { $$ = new_node(N_EXPR, 1, $1) }
	|	LEFT_PAREN expr RIGHT_PAREN { $$ = $2 }
    ;

unary_expr:
		INTEGER { $$ = new_leaf(N_UNARY_EXPR, yylval.val) }
	| 	FLOAT { $$ = new_leaf(N_UNARY_EXPR, yylval.val) }
	| 	identifier { $$ = new_node(N_UNARY_EXPR, 1, $1) }
	;

add_expr:
		expr PLUS expr { $$ = new_node(N_ADD_EXPR, 2, $1, $3) }
	;

sub_expr:
		expr MINUS expr { $$ = new_node(N_SUB_EXPR, 2, $1, $3) }
	;

mul_expr:
		expr STAR expr { $$ = new_node(N_MUL_EXPR, 2, $1, $3) }
	;

div_expr:
		expr SLASH expr { $$ = new_node(N_DIV_EXPR, 2, $1, $3) }
	;

variable_declaration_list:
		variable_declaration { $$ = new_node(N_VARIABLE_DECLARATION, 1, $1) }
	|	variable_declaration_list COMMA variable_declaration { $$ = flatten_list($1, $3) }
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