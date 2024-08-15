#ifndef MYLANG_C_AST_H
#define MYLANG_C_AST_H

#include <stddef.h>

typedef enum {
    N_OBJECT_FILE,
    N_FULL_TITLE,
    N_PRIMARY_TITLE,
    N_SECONDARY_TITLE,
    N_METHODS_BLOCK_LIST,
    N_METHODS_BLOCK,
    N_METHODS_LIST,
    N_METHOD,
    N_METHOD_SIGNATURE,
    N_METHOD_HEADER,
    N_STATEMENT_LIST,
    N_STATEMENT,
    N_LOCAL_DECLARATION,
    N_EXPR,
    N_UNARY_EXPR,
    N_ADD_EXPR,
    N_SUB_EXPR,
    N_MUL_EXPR,
    N_DIV_EXPR,
    N_PARAM_LIST,
    N_PARAM,
    N_FIELDS_BLOCK,
    N_FIELD_LIST,
    N_FIELD,
    N_VARIABLE_DECLARATION,
    N_IDENTIFIER,
    N_IDENTIFIER_LIST,
    N_TYPE,
    N_TYPE_LIST,
} NodeType;

typedef struct Node {
    char *value;
    NodeType node_type;
    size_t child_len;
    struct Node **children;
} Node;

Node *new_node(NodeType node_type, int child_len, ...);
Node *new_leaf(NodeType node_type, char *value);
Node *flatten_list(Node *list_node, Node* child);

#endif //MYLANG_C_AST_H
