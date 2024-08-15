#ifndef MYLANG_ANALYSER_H
#define MYLANG_ANALYSER_H

#include "ast/ast.h"
#include "utils/utils.h"
#include "types/object.h"



void analyse_ast(Node *root);
void visit_object_file(Node *object_file);
void visit_full_title(Node *full_title, Object *obj);
void visit_primary_title(Node *primary_title, Object *obj);
void visit_secondary_title(Node *secondary_title, Object *obj);
void visit_fields_block(Node *fields_block, Object *obj);
void visit_methods_block_list(Node *methods_block_list, Object *obj);
void visit_type_list(Node *type_list, Object *obj);

#endif //MYLANG_ANALYSER_H
