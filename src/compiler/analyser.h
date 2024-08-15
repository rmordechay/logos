#ifndef MYLANG_ANALYSER_H
#define MYLANG_ANALYSER_H

#include "ast/ast.h"
#include "utils/utils.h"
#include "types/object.h"
#include "types/method.h"


void analyse_ast(Node *root);
void visit_object_file(Node *n_object_file);
void visit_full_title(Node *n_full_title, Object *obj);
void visit_primary_title(Node *n_primary_title, Object *obj);
void visit_secondary_title(Node *n_secondary_title, Object *obj);
void visit_fields_block(Node *n_fields_block, Object *obj);
void visit_methods_block_list(Node *n_methods_block_list, Object *obj);
void visit_methods_block(Node *n_methods_block, Object *obj);
void visit_method(Node *n_method, Object *obj, Method *method);
void visit_field(Node *n_field, Field *field);
void visit_var_declaration(Node *n_var_declaration, Variable *variable);
void visit_variable(Node *n_variable, Variable *variable);
void visit_type(Node *n_type, Type *type);

#endif //MYLANG_ANALYSER_H
