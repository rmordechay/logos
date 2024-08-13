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

    for (int i = 0; i < childCount; i++) {
        ASTNode* arg = va_arg(args, ASTNode*);
        if (arg == NULL) {
            break;
        }
        if (arg->value == NULL) {
            continue;
        }
    }

    va_end(args);
    return NULL;
}

ASTNode *new_leaf(NodeType nodeType, char *value) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->value = value;
    node->nodeType = nodeType;
    return node;
}
