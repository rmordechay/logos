#ifndef MYLANG_C_AST_H
#define MYLANG_C_AST_H

#include "cJSON.h"
#include <stdio.h>

typedef enum {
    N_OBJECT_FILE,
    N_FULL_TITLE,
    N_PRIMARY_TITLE,
    N_SECONDARY_TITLE,
    N_METHODS_BLOCK_LIST,
    N_METHODS_BLOCK,
    N_METHODS_LIST,
    N_METHOD_SIGNATURE,
    N_METHOD_HEADER,
    N_METHOD,
    N_PARAM_LIST,
    N_PARAM,
    N_FULL_VARIABLE_DECLARATION,
    N_FIELDS_BLOCK,
    N_FIELD_LIST,
    N_FIELD,
    N_VARIABLE_DECLARATION,
    N_IDENTIFIER,
    N_TYPE,
} NodeType;

typedef struct ASTNode {
    char *value;
    NodeType nodeType;
    size_t childCount;
    struct ASTNode **children;
} ASTNode;

ASTNode *new_node(NodeType nodeType, int childCount, ...);
ASTNode *new_leaf(NodeType nodeType, char *value);


void visitNode(ASTNode *node);
void visitObjectFile(ASTNode *object_file);
void visitFullTitle(ASTNode *full_title);
void visitPrimaryTitle(ASTNode *primary_title);
void visitSecondaryTitle(ASTNode *secondary_title);

#endif //MYLANG_C_AST_H
