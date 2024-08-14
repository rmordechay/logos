#ifndef MYLANG_UTILS_H
#define MYLANG_UTILS_H

#include <cJSON.h>
#include <curl/curl.h>
#include "../ast/ast.h"

char *get_node_string(NodeType nodeType);
void print_tree(ASTNode *root, int depth);
cJSON *node_to_json(ASTNode * node);
void print_json(ASTNode *node);

#endif //MYLANG_UTILS_H
