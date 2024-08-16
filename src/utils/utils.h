#ifndef UTILS_H
#define UTILS_H

#include "cJSON.h"
#include <curl/curl.h>
#include "ast/ast.h"

typedef struct StringList {
    char **strings;
    int len;
    int capacity;
} StringList;


char *get_node_string(NodeType nodeType);
void print_tree(Node *root, int depth);
cJSON *node_to_json(Node * node);

void init_string_list(StringList *list, int capacity);
void add_to_string(StringList *list, const char *str);
const char *get_string_element(StringList *list, int i);

void print_json(Node *node);

#endif //UTILS_H
