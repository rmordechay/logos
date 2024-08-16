#ifndef UTILS_H
#define UTILS_H

#include "cJSON.h"
#include "ast/tree.h"
#include <curl/curl.h>

typedef struct StringList {
    char **strings;
    int len;
    int capacity;
} StringList;

void init_string_list(StringList *list, int capacity);
void add_to_string(StringList *list, const char *str);
const char *get_string_element(StringList *list, int i);

#endif //UTILS_H
