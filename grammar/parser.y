%{
#include <stdio.h>
#include <stdlib.h>
#include "ast/tree.h"

extern int yylex();
extern int yyparse();
extern int yylineno;
extern FILE* yyin;
void yyerror(const char* s);

struct Entity *root;

%}

%union {
char* val;
struct Node *node;
struct ObjectEntity *object_entity;
struct InterfaceEntity *interface_entity;
struct ImplementsBlock *implements_block;
struct ObjectFieldList *object_field_list;
struct ObjectField *object_field;
struct InterfaceFieldList *interface_field_list;
struct InterfaceField *interface_field;
struct Carrier *carrier;
struct MethodSignature *method_signature;
struct ObjectMethodsBlockList *object_methods_block_list;
struct ObjectMethodsBlock *object_methods_block;
struct ObjectMethodsList *object_methods_list;
struct ObjectMethod *object_method;
struct InterfaceMethodsBlockList *interface_methods_block_list;
struct InterfaceMethodsBlock *interface_methods_block;
struct InterfaceMethodsList *interface_methods_list;
struct InterfaceMethod *interface_method;
struct StatementList *statement_list;
struct Statement *statement;
struct IterationStmt *iteration_statement;
struct IterationStmtList *iteration_statement_list;
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
struct Iteration *iteration;
struct ForInLoop *for_in_loop;
struct WhileLoop *while_loop;
struct ReturnStatement *return_statement;
struct Expr *expr;
struct ExprList *expr_list;
struct BinaryExpr *binary_expr;
struct UnaryExpr *unary_expr;
struct MethodCall *method_call;
struct VariableDecList *variable_declaration_list;
struct VariableDec *variable_declaration;
struct Collection *collection;
struct EnumDeclaration *enum_declartion;
struct Type *type;
struct TypeList *type_list;
struct ConstantVariable *constant_variable;
struct ConstantVariableList *constant_variable_list;
struct Identifier *identifier;
struct IdentifierList *identifier_list;
}

%start program

%token AND OR NOT
%token RETURN BREAK CONTINUE
%token OBJECT INTERFACE IMPLEMENTS FIELDS IMPORT ENUM CARRIER
%token LET FUNC IF FOR IN CONST
%token LEFT_PAREN RIGHT_PAREN LEFT_BRACE RIGHT_BRACE LEFT_BRACKET RIGHT_BRACKET LEFT_ANGLE RIGHT_ANGLE
%token COMMA DOT COLON EQUAL MINUS PLUS STAR SLASH HASH QUEST_MARK EXCLA_MARK PERCENT DOLLAR AMPERSAND
%token <val> INTEGER FLOAT IDENTIFIER BOOL STRING TYPE

%type <object_entity> program
%type <object_entity> object_entity
%type <interface_entity> interface_entity
%type <implements_block> implements_block
%type <object_field_list> object_field_list object_fields_block
%type <object_field> object_field
%type <interface_field_list> interface_field_list interface_fields_block
%type <interface_field> interface_field
%type <carrier> carrier
%type <object_methods_block_list> object_methods_block_list
%type <object_methods_block> object_methods_block
%type <object_methods_list> object_methods_list
%type <object_method> object_method
%type <interface_methods_block_list> interface_methods_block_list
%type <interface_methods_block> interface_methods_block
%type <interface_methods_list> interface_methods_list
%type <interface_method> interface_method
%type <method_signature> method_signature
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
%type <iteration> iteration
%type <for_in_loop> for_in_loop
%type <while_loop> while_loop
%type <return_statement> return_statement
%type <expr> expr
%type <expr_list> expr_list
%type <binary_expr> binary_expr
%type <binary_expr> add_expr
%type <binary_expr> sub_expr
%type <binary_expr> mul_expr
%type <binary_expr> div_expr
%type <unary_expr> unary_expr
%type <method_call> method_call
%type <variable_declaration_list> variable_declaration_list
%type <variable_declaration> variable_declaration
%type <collection> collection
%type <enum_declartion> enum_declartion
%type <type> type
%type <type_list> type_list
%type <constant_variable> constant_variable
%type <constant_variable_list> constant_variable_list
%type <identifier> identifier
%type <identifier_list> identifier_list

%%
program:
		object_entity { root = create_entity(E_OBJECT, $1) }
	|	interface_entity { root = create_entity(E_INTERFACE, $1) }
	;

object_entity:
		OBJECT COLON type implements_block enum_declartion object_fields_block object_methods_block_list { $$ = create_object_entity($3, $4, $6, $7) }
	| 	OBJECT COLON type implements_block object_fields_block object_methods_block_list { $$ = create_object_entity($3, $4, $5, $6) }
	| 	OBJECT COLON type object_fields_block { $$ = create_object_entity($3, NULL, $4, NULL) }
	;

interface_entity:
		INTERFACE COLON type interface_fields_block interface_methods_block_list { $$ = create_interface_entity($3, $4)  }
	;

implements_block:
		IMPLEMENTS LEFT_BRACE type_list RIGHT_BRACE { $$ = create_implements_block($3) }
	;

object_fields_block:
		FIELDS LEFT_BRACE object_field_list RIGHT_BRACE { $$ = $3 }
	;

object_field_list:
		object_field { $$ = create_object_field_list($1) }
	| 	object_field_list object_field { $$ = add_object_field($1, $2) }
	;

object_field:
		variable_declaration COLON type  { $$ = create_object_field($1, $3)  }
	|	variable_declaration  { $$ = create_object_field($1, NULL)  }
	;

interface_fields_block:
		FIELDS LEFT_BRACE interface_field_list RIGHT_BRACE { $$ = $3 }
	;

interface_field_list:
		interface_field { $$ = create_interface_field_list($1) }
	| 	interface_field_list interface_field { $$ = add_interface_field($1, $2) }
	;

interface_field:
		variable_declaration  { $$ = create_interface_field($1)  }
	;

object_methods_block_list:
		object_methods_block {  $$ = create_object_methods_block_list($1);  }
	|	object_methods_block_list object_methods_block {  $$ = add_object_methods_block($1, $2);  }
	;

object_methods_block:
		type LEFT_BRACE object_methods_list RIGHT_BRACE { $$ = create_object_methods_block($1, $3) }
	|	type LEFT_BRACE enum_declartion object_methods_list RIGHT_BRACE { $$ = create_object_methods_block($1, $4) }
	;

object_methods_list:
		object_method { $$ = create_object_methods_list($1) }
	|	object_methods_list object_method { $$ = add_object_method($1, $2) }
	;

object_method:
		method_signature statements_block carrier { $$ = create_object_method($1, $2, $3) }
	|	method_signature statements_block { $$ = create_object_method($1, $2, NULL) }
	;

carrier:
		CARRIER identifier_list
	;

interface_methods_block_list:
		interface_methods_block {  $$ = create_interface_methods_block_list($1);  }
	|	interface_methods_block_list interface_methods_block {  $$ = add_interface_methods_block($1, $2);  }
	;

interface_methods_block:
		type LEFT_BRACE interface_methods_list RIGHT_BRACE { $$ = create_interface_methods_block($1, $3) }
	|	type LEFT_BRACE enum_declartion interface_methods_list RIGHT_BRACE { $$ = create_interface_methods_block($1, $4) }
	;

interface_methods_list:
		interface_method { $$ = create_interface_methods_list($1) }
	|	interface_methods_list interface_method { $$ = add_interface_method($1, $2) }
	;

interface_method:
		method_signature statements_block { $$ = create_interface_method($1, $2) }
	|	method_signature { $$ = create_interface_method($1, NULL) }
	;

method_signature:
		FUNC variable_declaration LEFT_PAREN variable_declaration_list RIGHT_PAREN { $$ = create_method_signature($2, $4) }
	|	FUNC variable_declaration LEFT_PAREN RIGHT_PAREN { $$ = create_method_signature($2, NULL) }
	;

statements_block:
		LEFT_BRACE statement_list RIGHT_BRACE { $$ = $2 }
	|	LEFT_BRACE RIGHT_BRACE { $$ = create_statement_list(NULL) }
	;

statement_list:
		statement { $$ = create_statement_list($1) }
	|	statement_list statement { $$ = add_statement($1, $2) }
	;

statement:
		local_declaration { $$ = create_stmt_from_local_dec($1) }
	|	enum_declartion  { $$ = create_stmt_from_enum($1) }
	|	if_statement { $$ = create_stmt_from_if_stmt($1);  }
	|	pattern_matching  { $$ = create_stmt_from_pm($1);  }
	|	pattern_matching_expr  { $$ = create_stmt_from_pme($1);  }
	|	iteration  { $$ = create_stmt_from_iteration($1); }
	|	return_statement  { $$ = create_stmt_from_return($1);  }
	|	CONTINUE  { $$ = create_stmt_from_continue();  }
	|	BREAK expr  { $$ = create_stmt_from_break($2);  }
	|	expr  { $$ = create_stmt_from_expr($1);  }
	;

local_declaration:
		LET type identifier EQUAL expr { $$ = create_local_declaration($2, $3, $5) }
	|	LET identifier EQUAL expr { $$ = create_local_declaration(NULL, $2, $4) }
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
	|	if_or_block_list if_or_block { $$ = add_if_or_block($1, $2) }
	;

if_or_block:
		OR expr statements_block { $$ = create_if_or_block($2, $3) }
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
	|	pattern_list pattern { $$ =  add_pattern($1, $2) }
	;

pattern:
		expr COLON expr { $$ = create_pattern_from_expr($1, $3) }
	|	expr COLON statements_block { $$ = create_pattern_from_stmt_list($1, $3) }
	|	OR COLON expr { $$ = create_pattern_from_expr(NULL, $3) }
	|	OR COLON statements_block { $$ = create_pattern_from_stmt_list(NULL, $3) }
	;

iteration:
		FOR statements_block { $$ = create_iteration_from_inf_loop($2) }
	|	while_loop statements_block { $$ = create_iteration_from_while($1, $2) }
	|	for_in_loop statements_block { $$ = create_iteration_from_for_in($1, $2) }
	;

for_in_loop:
		FOR expr_list IN expr { $$ = create_for_in_loop($2, $4) }
	;

while_loop:
		FOR expr_list { $$ = create_while_loop($2) }
	;

return_statement:
		RETURN expr_list { $$ = create_return_statement($2) }
	|	RETURN { $$ = create_return_statement(NULL) }
	;

expr_list:
		expr { $$ = create_expr_list($1) }
	|	expr_list COMMA expr { $$ =  add_expr($1, $3) }
	|	LEFT_PAREN expr_list RIGHT_PAREN { $$ =  $2 }
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
		method_call { $$ = create_unary_expr_from_method_call($1) }
	| 	identifier { $$ = create_unary_expr_from_id($1) }
	| 	collection { $$ = create_unary_expr_from_collection($1) }
	| 	INTEGER { $$ = create_unary_expr_from_number(INTEGER, yylval.val) }
	| 	FLOAT { $$ = create_unary_expr_from_number(FLOAT, yylval.val) }
	| 	BOOL { $$ = create_unary_expr_from_number(BOOL, yylval.val) }
	| 	STRING { $$ = create_unary_expr_from_string(yylval.val) }
	;

method_call:
		identifier LEFT_PAREN expr_list RIGHT_PAREN { $$ = create_method_call($1, $3) }
	|	identifier LEFT_PAREN RIGHT_PAREN { $$ = create_method_call($1, NULL) }
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

collection:
		TYPE LEFT_BRACKET expr_list RIGHT_BRACKET  {  }
	|	type  { $$ = create_collection($1, NULL) }
	|	LEFT_BRACKET expr_list RIGHT_BRACKET  { $$ = create_collection(NULL, $2) }
	;

enum_declartion:
		ENUM type LEFT_BRACE constant_variable_list RIGHT_BRACE { $$ = create_enum_declaration($2, $4)  }
	;


variable_declaration_list:
		variable_declaration { $$ = create_var_dec_list($1) }
	|	variable_declaration_list COMMA variable_declaration { $$ = add_var_dec($1, $3) }
	;

variable_declaration:
		type identifier { $$ = create_variable_declaration($1, $2) }
	;

type:
		TYPE { $$ = create_type(yylval.val) }
    ;

type_list:
	  	type { $$ = create_type_list($1)  }
	| 	type_list COMMA type { $$ = add_type($1, $3)  }
	;

constant_variable:
		CONST { $$ = create_constant_variable(yylval.val) }
	;

constant_variable_list:
		constant_variable { $$ = create_const_var_list($1)  }
	|	constant_variable_list constant_variable { $$ = add_const_var($1, $2)  }
	;

identifier:
		IDENTIFIER { $$ = create_identifier(yylval.val) }
	;

identifier_list:
	  	identifier { $$ = create_identifier_list($1)  }
	| 	identifier_list COMMA identifier { $$ = add_identifier($1, $3)  }
	| 	LEFT_PAREN identifier_list RIGHT_PAREN { $$ = $2  }
	;

%%

void yyerror(const char* s) {
    fprintf(stderr, "Parse error on line %d: %s\n", yylineno, s);
    exit(1);
}
