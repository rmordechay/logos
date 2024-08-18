%{
#include <stdio.h>
#include <stdlib.h>
#include "ast/tree.h"

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
	struct IfStatement *if_statement;
    struct IfBlock *if_block;
    struct IfOrBlockList *if_or_block_list;
    struct IfOrBlock *if_or_block;
    struct OrBlock *or_block;
    struct PatternMatchingExpr *pattern_matching_expr;
    struct PatternMatching *pattern_matching;
    struct Pattern *pattern;
    struct PatternList *pattern_list;
	struct Expr *expr;
	struct ExprList *expr_list;
	struct BinaryExpr *binary_expr;
	struct UnaryExpr *unary_expr;
	struct VariableDeclarationList *variable_declaration_list;
	struct VariableDeclaration *variable_declaration;
	struct Identifier *identifier;
	struct Type *type;
	struct TypeList *type_list;
}

%start program

%token BOOL
%token LET FUNC IMPLEMENTS FIELDS SELF OBJECT IF FOR RETURN IMPORT AND OR NOT IN
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
%type <statement_list> statement_list statements_block
%type <statement> statement
%type <local_declaration> local_declaration
%type <if_statement> if_statement
%type <if_block> if_block
%type <if_or_block_list> if_or_block_list
%type <if_or_block> if_or_block
%type <or_block> or_block
%type <pattern_matching_expr> pattern_matching_expr
%type <pattern_matching> pattern_matching
%type <pattern> pattern
%type <pattern_list> pattern_list
%type <expr> expr
%type <expr_list> expr_list
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
    	variable_declaration COLON type  { $$ = create_field($1, $3)  }
    |	variable_declaration  { $$ = create_field($1, NULL)  }
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
		method_signature statements_block { $$ = create_method($1, $2) }
	;

method_signature:
		method_header LEFT_PAREN variable_declaration_list RIGHT_PAREN { $$ = create_method_signature($1, $3) }
	|	method_header LEFT_PAREN RIGHT_PAREN { $$ = create_method_signature($1, NULL) }
	;

method_header:
		FUNC variable_declaration { $$ = create_method_header($2) }
	;

statements_block:
		LEFT_BRACE RIGHT_BRACE { $$ = create_statement_list(NULL) }
	|	LEFT_BRACE statement_list RIGHT_BRACE { $$ = $2 }
	;

statement_list:
		statement { $$ = create_statement_list($1) }
	|	statement_list statement { $$ = flatten_statement_list($1, $2) }
	;

statement:
		local_declaration { $$ = create_stmt_from_local_dec($1) }
	|	if_statement { $$ = create_stmt_from_if_stmt($1);  }
	|	pattern_matching  { $$ = create_stmt_from_pm($1);  }
	|	pattern_matching_expr  { $$ = create_stmt_from_pme($1);  }
	;

local_declaration:
		LET variable_declaration EQUAL expr { $$ = create_local_declaration($2, $4) }
	;

if_statement:
		if_block if_or_block_list or_block { $$ = create_if_statement($1, $2, $3) }
	|	if_block if_or_block_list { $$ = create_if_statement($1, $2, NULL) }
	|	if_block or_block { $$ = create_if_statement($1, NULL, $2) }
	|	if_block { $$ = create_if_statement($1, NULL, NULL) }
	;

if_block:
      IF expr statements_block { $$ = create_if_block($2, $3) }
    ;

if_or_block_list:
		if_or_block { $$ = create_if_or_block_list($1) }
	|	if_or_block_list if_or_block { $$ = flatten_if_or_block_list($1, $2) }
	;

if_or_block:
      OR expr statements_block { $$ = create_if_block($2, $3) }
    ;


or_block:
      OR statements_block { $$ = create_or_block($2) }
    ;

pattern_matching:
		IF LEFT_BRACE pattern_list RIGHT_BRACE { $$ = create_pattern_matching($3) }
	;

pattern_matching_expr:
		IF expr LEFT_BRACE pattern_list RIGHT_BRACE { $$ = create_pattern_matching_expr($2, $4) }
	;

pattern_list:
		pattern { $$ = create_pattern_list($1) }
	|	pattern_list pattern { $$ =  flatten_pattern_list($1, $2) }
	;

pattern:
		expr COLON expr { $$ = create_pattern_from_expr($1, $3) }
	|	expr COLON statements_block { $$ = create_pattern_from_stmt_list($1, $3) }
	|	OR COLON expr { $$ = create_pattern_from_expr(NULL, $3) }
	|	OR COLON statements_block { $$ = create_pattern_from_stmt_list(NULL, $3) }
	;

expr_list:
		expr { $$ = create_expr_list($1) }
	|	expr_list expr { $$ =  flatten_expr_list($1, $2) }
    ;

expr:
		unary_expr { $$ = create_expr_from_unary($1) }
	|	binary_expr { $$ = create_expr_from_binary($1) }
	|	LEFT_PAREN expr RIGHT_PAREN { $$ = $2 }
    ;

binary_expr:
		add_expr
	|	sub_expr
	|	mul_expr
	|	div_expr
	;

unary_expr:
		INTEGER { $$ = create_unary_expr_from_number(INTEGER, yylval.val) }
	| 	FLOAT { $$ = create_unary_expr_from_number(FLOAT, yylval.val) }
	| 	BOOL { $$ = create_unary_expr_from_number(BOOL, yylval.val) }
	| 	identifier { $$ = create_unary_expr_from_id($1) }
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