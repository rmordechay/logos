#include <string.h>
#include <stdarg.h>
#include <printf.h>
#include <stdlib.h>
#include "ast.h"


/**
 *
 */
ASTNode *new_node(NodeType nodeType, int childCount, ...) {
    va_list args;
    va_start(args, childCount);

    ASTNode *node = malloc(sizeof(ASTNode));
    node->nodeType = nodeType;
    node->childCount = childCount;
    node->children = malloc(childCount * sizeof(ASTNode*));
    for (int i = 0; i < childCount; i++) {
        ASTNode* child = va_arg(args, ASTNode*);
        node->children[i] = child;
    }
    va_end(args);
    return node;
}

ASTNode *new_leaf(NodeType nodeType, char *value) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->value = value;
    node->nodeType = nodeType;
    return node;
}

char *get_node_string(NodeType nodeType) {
    switch(nodeType) {
        case N_OBJECT_FILE: return "OBJECT_FILE";
        case N_TITLE: return "TITLE";
        case N_PRIMARY_TITLE: return "PRIMARY_TITLE";
        case N_SECONDARY_TITLE: return "SECONDARY_TITLE";
        case N_METHODS_BLOCK_LIST: return "METHODS_BLOCK_LIST";
        case N_METHODS_BLOCK: return "METHODS_BLOCK";
        case N_METHODS_LIST: return "METHODS_LIST";
        case N_METHOD_SIGNATURE: return "METHOD_SIGNATURE";
        case N_METHOD_HEADER: return "METHOD_HEADER";
        case N_METHOD: return "METHOD";
        case N_PARAM_LIST: return "PARAM_LIST";
        case N_PARAM: return "PARAM";
        case N_FULL_VARIABLE_DECLARATION: return "FULL_VARIABLE_DECLARATION";
        case N_FIELDS_BLOCK: return "FIELDS_BLOCK";
        case N_FIELD_LIST: return "FIELD_LIST";
        case N_FIELD: return "FIELD";
        case N_VARIABLE_DECLARATION: return "VARIABLE_DECLARATION";
        case N_IDENTIFIER: return "IDENTIFIER";
        case N_TYPE: return "TYPE";
        default: return "UNKNOWN_TYPE";
    }
}
