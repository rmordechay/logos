#ifndef MYLANG_ANALYSER_H
#define MYLANG_ANALYSER_H

#include "ast/ast.h"
#include "utils/utils.h"
#include "types/object.h"



void analyse_ast(Node *root);
void visit_object_file(Node *n_object_file);
void visit_full_title(Node *n_full_title, Object *obj);
void visit_primary_title(Node *n_primary_title, Object *obj);
void visit_secondary_title(Node *n_secondary_title, Object *obj);
void visit_fields_block(Node *n_fields_block, Object *obj);
void visit_methods_block_list(Node *n_methods_block_list, Object *obj);
void visit_field(Node *n_field, Object *obj, Field *field);
void visit_var_declaration(Node *n_var_declaration, Object *obj, Field *field);
void visit_variable(Node *n_variable, Object *obj, Variable *p_variable);
void visit_type(Node *n_type, Object *obj, Type *type);

#endif //MYLANG_ANALYSER_H
