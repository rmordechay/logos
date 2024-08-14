#include "ast.h"


/**
 *
 */
ASTNode *new_node(NodeType node_type, int child_count, ...) {
    va_list args;
    va_start(args, child_count);

    ASTNode *node = malloc(sizeof(ASTNode));
    node->node_type = node_type;
    node->child_count = child_count;
    node->children = malloc(child_count * sizeof(ASTNode *));
    for (int i = 0; i < child_count; i++) {
        ASTNode *child = va_arg(args, ASTNode*);
        node->children[i] = child;
    }
    va_end(args);
    return node;
}

/**
 *
 */
ASTNode *new_leaf(NodeType node_type, char *value) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->value = value;
    node->node_type = node_type;
    return node;
}

/**
 *
 */
char *get_node_string(NodeType nodeType) {
    switch (nodeType) {
        case N_OBJECT_FILE: return "OBJECT_FILE";
        case N_FULL_TITLE: return "TITLE";
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

