#ifndef ANALYSER_H
#define ANALYSER_H

#include "ast/ast.h"
#include "utils/utils.h"
#include "types/types.h"


void analyse_ast(Node *root);
void visit_object_file(Node *n_object_file);
void visit_full_title(Node *n_full_title, Object *obj);
void visit_primary_title(Node *n_primary_title, Object *obj);
void visit_secondary_title(Node *n_secondary_title, Object *obj);
void visit_fields_block(Node *n_fields_block, Object *obj);
void visit_methods_block_list(Node *n_methods_block_list, Object *obj);
void visit_methods_block(Node *n_methods_block, MethodBlock *method_block);
void visit_methods_signature(Node *n_method_signature, Method *p_method);
void visit_param_list(Node *n_param_list, Method *p_method);
void visit_variable_declaration(Node *n_var_dec, VariableDec *param);
void visit_method(Node *n_method, Method *method);
void visit_field(Node *n_field, Field *field);
void visit_stmt_list(Node *n_stmt_list, Method *method);
void visit_statement(Node *n_stmt);
void visit_local_declaration(Node *n_local_declaration, LocalDec *local_dec);
void visit_expr(Node *n_expr, Expr *expr);

#endif //ANALYSER_H
