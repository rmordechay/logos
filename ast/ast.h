#ifndef MYLANG_C_AST_H
#define MYLANG_C_AST_H

typedef enum NodeType {
    A,
    B,
} NodeType;

typedef struct ASTNode {
    int nodeType;
//    struct ASTNode *left;
//    struct ASTNode *right;
} ASTNode;

#endif //MYLANG_C_AST_H
