#include <stdarg.h>
#include <stdlib.h>
#include "ast.h"
#include "utils/utils.h"


/**
 *
 */
Node *new_node(NodeType node_type, int child_len, ...) {
    va_list args;
    va_start(args, child_len);
    Node *node = malloc(sizeof(Node));
    node->node_type = node_type;
    node->child_len = child_len;
    node->children = malloc(child_len * sizeof(Node *));
    for (int i = 0; i < child_len; i++) {
        Node *child = va_arg(args, Node*);
        node->children[i] = child;
    }
    va_end(args);
    return node;
}

Node *flatten_list(Node *list_node, Node* child) {
    size_t new_len = list_node->child_len + 1;
    list_node->children = realloc(list_node->children, new_len * sizeof(Node *));
    list_node->children[list_node->child_len] = child;
    list_node->child_len = new_len;
    return list_node;
}

/**
 *
 */
Node *new_leaf(NodeType node_type, char *value) {
    Node *node = malloc(sizeof(Node));
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
        case N_PARAM: return "PARAM";
        case N_VARIABLE_DECLARATION: return "VARIABLE_DECLARATION";
        case N_FIELDS_BLOCK: return "FIELDS_BLOCK";
        case N_FIELD_LIST: return "FIELD_LIST";
        case N_FIELD: return "FIELD";
        case N_IDENTIFIER: return "IDENTIFIER";
        case N_TYPE: return "TYPE";
        case N_TYPE_LIST: return "TYPE_LIST";
        case N_STATEMENT_LIST: return "STATEMENT_LIST";
        case N_STATEMENT: return "STATEMENT";
        case N_EXPR: return "EXPR";
        case N_UNARY_EXPR: return "UNARY_EXPR";
        case N_ADD_EXPR: return "ADD_EXPR";
        case N_SUB_EXPR: return "SUB_EXPR";
        case N_MUL_EXPR: return "MUL_EXPR";
        case N_DIV_EXPR: return "DIV_EXPR";
        case N_IDENTIFIER_LIST: return "IDENTIFIER_LIST";
        case N_LOCAL_DECLARATION: return "LOCAL_DECLARATION";
        case N_VAR_DEC_LIST: return "VAR_DEC_LIST";
        case N_BINARY_EXPR:break;
        default: return NULL;

    }
    return NULL;
}

