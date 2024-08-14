#ifndef MYLANG_ANALYSER_H
#define MYLANG_ANALYSER_H

#include "../ast/ast.h"
#include "../utils/utils.h"

void analyse_ast(ASTNode *root);
void visit_object_file(ASTNode *object_file);
void visit_full_title(ASTNode *full_title);
void visit_primary_title(ASTNode *primary_title);
void visit_secondary_title(ASTNode *secondary_title);
void visit_fields_block(ASTNode *fields_block);
void visit_methods_block_list(ASTNode *methods_block_list);

#endif //MYLANG_ANALYSER_H
