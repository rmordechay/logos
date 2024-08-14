#ifndef MYLANG_C_AST_H
#define MYLANG_C_AST_H


typedef enum {
    N_OBJECT_FILE,
    N_TITLE,
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
char *get_node_string(NodeType nodeType);
void print_node(ASTNode *root, int depth);

#endif //MYLANG_C_AST_H
