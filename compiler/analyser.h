#ifndef MYLANG_ANALYSER_H
#define MYLANG_ANALYSER_H

#include "../ast/ast.h"
#include "../utils/utils.h"

typedef struct Object {
    char *name;
    StringList implements;
    size_t implements_count;
} Object;

Object *create_object();
void analyse_ast(ASTNode *root);
void visit_object_file(ASTNode *object_file);
void visit_full_title(ASTNode *full_title, Object *obj);
void visit_primary_title(ASTNode *primary_title, Object *obj);
void visit_secondary_title(ASTNode *secondary_title, Object *obj);
void visit_fields_block(ASTNode *fields_block, Object *obj);
void visit_methods_block_list(ASTNode *methods_block_list, Object *obj);
void visit_type_list(ASTNode *type_list, Object *obj);

#endif //MYLANG_ANALYSER_H
