%{
#include <stdio.h>
#include <stdlib.h>
#include "ast/tree.h"
#include "utils/utils.h"

extern int yylex();
extern int yyparse();
extern int yylineno;
extern FILE* yyin;
void yyerror(const char* s);

struct ObjectFile *root;

%}

%union {
    char* val;
    struct Node *node;
	struct ObjectFile *object_file;
	struct ImplementsBlock *implements_block;
	struct FieldsBlock *fields_block;
	struct FieldList *field_list;
	struct Field *field;
	struct MethodsBlockList *methods_block_list;
	struct MethodsBlock *methods_block;
	struct MethodsList *methods_list;
	struct Method *method;
	struct MethodSignature *method_signature;
	struct MethodHeader *method_header;
	struct StatementList *statement_list;
	struct Statement *statement;
	struct LocalDeclaration *local_declaration;
	struct Expr *expr;
	struct BinaryExpr *binary_expr;
	struct UnaryExpr *unary_expr;
	struct VariableDeclarationList *variable_declaration_list;
	struct VariableDeclaration *variable_declaration;
	struct Identifier *identifier;
	struct Type *type;
	struct TypeList *type_list;
}

%start program

%token LET FUNC IMPLEMENTS FIELDS SELF OBJECT IF FOR RETURN IMPORT AND OR NOT
%token LEFT_PAREN RIGHT_PAREN LEFT_BRACE RIGHT_BRACE LEFT_BRACKET RIGHT_BRACKET LEFT_ANGLE RIGHT_ANGLE
%token COMMA DOT COLON EQUAL MINUS PLUS STAR SLASH HASH QUEST_MARK EXCLA_MARK PERCENT DOLLAR AMPERSAND
%token <val> INTEGER FLOAT IDENTIFIER

%type <object_file> program
%type <object_file> object_file
%type <implements_block> implements_block
%type <fields_block> fields_block
%type <field_list> field_list
%type <field> field
%type <methods_block_list> methods_block_list
%type <methods_block> methods_block
%type <methods_list> methods_list
%type <method> method
%type <method_signature> method_signature
%type <method_header> method_header
%type <statement_list> statement_list
%type <statement> statement
%type <local_declaration> local_declaration
%type <expr> expr
%type <unary_expr> unary_expr
%type <binary_expr> binary_expr
%type <binary_expr> add_expr
%type <binary_expr> sub_expr
%type <binary_expr> mul_expr
%type <binary_expr> div_expr
%type <variable_declaration_list> variable_declaration_list
%type <variable_declaration> variable_declaration
%type <identifier> identifier
%type <type> type
%type <type_list> type_list

%%

program:
    	object_file { analyse_ast($1) }
    ;

object_file:
      	OBJECT COLON identifier implements_block fields_block methods_block_list { $$ = create_object_file($3, $4, $5, $6) }
    | 	OBJECT COLON identifier fields_block { $$ = create_object_file($3, NULL, $4, NULL) }
    ;

implements_block:
		IMPLEMENTS LEFT_BRACE type_list RIGHT_BRACE { $$ = create_implements_block($3) }
	;

fields_block:
      	FIELDS LEFT_BRACE field_list RIGHT_BRACE { $$ = create_fields_block($3) }
    ;

field_list:
		field { $$ = create_field_list($1) }
    | 	field_list field { $$ = flatten_field_list($1, $2) }
    ;

field:
    	variable_declaration  { $$ = create_field($1, NULL)  }
    |	variable_declaration COLON type  { $$ = create_field($1, $3)  }
    ;

methods_block_list:
		methods_block {  $$ = create_methods_block_list($1);  }
	|	methods_block_list methods_block {  $$ = flatten_methods_block_list($1, $2);  }
	;

methods_block:
		identifier LEFT_BRACE methods_list RIGHT_BRACE { $$ = create_methods_block($1, $3) }
	;

methods_list:
		method { $$ = create_methods_list($1) }
	|	methods_list method { $$ = flatten_methods_list($1, $2) }
	;

method:
		method_signature LEFT_BRACE statement_list RIGHT_BRACE { $$ = create_method($1, $3) }
	|	method_signature LEFT_BRACE RIGHT_BRACE { $$ = create_method($1, NULL) }
	;

method_signature:
		method_header LEFT_PAREN variable_declaration_list RIGHT_PAREN { $$ = create_method_signature($1, $3) }
	|	method_header LEFT_PAREN RIGHT_PAREN { $$ = create_method_signature($1, NULL) }
	;

method_header:
		FUNC variable_declaration { $$ = create_method_header($2) }
	;


statement_list:
		statement { $$ = create_statement_list($1) }
	|	statement_list statement { $$ = flatten_statement_list($1, $2) }
	;

statement:
		local_declaration { $$ = create_statement($1) }
	;

local_declaration:
		LET variable_declaration EQUAL expr { $$ = create_local_declaration($2, $4) }
	;

expr:
		unary_expr { $$ = create_expr_unary($1) }
	|	binary_expr { $$ = create_expr_binary($1) }
	|	LEFT_PAREN expr RIGHT_PAREN { $$ = $2 }
    ;

binary_expr:
		add_expr
	|	sub_expr
	|	mul_expr
	|	div_expr
	;

unary_expr:
		INTEGER { $$ = create_unary_expr_int(yylval.val) }
	| 	FLOAT { $$ = create_unary_expr_float(yylval.val) }
	| 	identifier { $$ = create_unary_expr_id($1) }
	;

add_expr:
		expr PLUS expr { $$ = create_binary_expr($1, $3, '+') }
	;

sub_expr:
		expr MINUS expr { $$ = create_binary_expr($1, $3, '-') }
	;

mul_expr:
		expr STAR expr { $$ = create_binary_expr($1, $3, '*') }
	;

div_expr:
		expr SLASH expr { $$ = create_binary_expr($1, $3, '/') }
	;

variable_declaration_list:
		variable_declaration { $$ = create_var_dec_list($1) }
	|	variable_declaration_list COMMA variable_declaration { $$ = flatten_var_dec_list($1, $3) }
	;

variable_declaration:
		type identifier { $$ = create_variable_declaration($1, $2) }
	;

identifier:
		IDENTIFIER { $$ = create_identifier(yylval.val) }
	;

type:
    	IDENTIFIER { $$ = create_type(yylval.val) }
    ;

type_list:
	  	type { $$ = create_type_list($1)  }
	| 	type_list COMMA type { $$ = flatten_type_list($1, $3)  }
	;
%%

void yyerror(const char* s) {
    fprintf(stderr, "Parse error on line %d: %s\n", yylineno, s);
    exit(1);
}