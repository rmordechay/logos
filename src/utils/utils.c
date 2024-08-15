#include <strings.h>
#include <stdlib.h>
#include "utils.h"

/**
 *
 */
void make_http_call() {
    CURL *curl;
    CURLcode res;

    const char *json = "";

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (!curl) return;
    curl_easy_setopt(curl, CURLOPT_URL, "");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json);

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    curl_share_cleanup(headers);
}

/**
 *
 */
void print_tree(Node *root, int depth) {
    for (int i = 0; i < depth; i++) {
        printf("\t");
    }
    printf("- Node Type: %s\n", get_node_string(root->node_type));
    if (root->child_len != 0) {
        for (int i = 0; i < depth; i++) {
            printf("\t");
        }
        printf("  Child len: %zu\n", root->child_len);
        for (int i = 0; i < depth; i++) {
            printf("\t");
        }
        printf("  Children:\n");
        for (size_t i = 0; i < root->child_len; i++) {
            print_tree(root->children[i], depth + 1);
        }
    } else {
        for (int i = 0; i < depth; i++) {
            printf("\t");
        }
        printf("  Value: %s\n", root->value);
    }
}


cJSON *node_to_json(Node * node) {
    if (node == NULL) {
        return NULL;
    }
    cJSON *json = cJSON_CreateObject();
    if (node->value != NULL) {
        cJSON_AddStringToObject(json, "value", node->value);
    } else {
        cJSON_AddNullToObject(json, "value");
    }
    cJSON_AddStringToObject(json, "node_type", get_node_string(node->node_type));
    cJSON *arr = cJSON_CreateArray();
    for (int i = 0; i < node->child_len; i++) {
        cJSON *child = (cJSON *) node_to_json(node->children[i]);
        if (child != NULL) {
            cJSON_AddItemToArray(arr, child);
        }
    }
    cJSON_AddItemToObject(json, "children", arr);
    return json;
}

/**
 *
 */
void print_json(Node *node) {
    cJSON *json = node_to_json(node);
    char *jsonString = cJSON_Print(json);
    cJSON_Delete(json);
    printf("%s\n", jsonString);
}

/**
 *
 */
void init_string_list(StringList *list, int capacity) {
    list->capacity = capacity;
    list->len = 0;
    list->strings = malloc(capacity * sizeof(char *));
}

/**
 *
 */
void add_to_string(StringList *list, const char *str) {
    if (list->len >= list->capacity) {
        list->capacity *= 2;
        char **new_string = realloc(list->strings, list->capacity * sizeof(char *));
        list->strings = new_string;
    }
    list->strings[list->len] = malloc(strlen(str) + 1);
    strcpy(list->strings[list->len], str);
    list->len++;
}

/**
 *
 */
const char *get_string_element(StringList *list, int i) {
    if (i < 0 || i > list->len) return NULL;
    return list->strings[i];
}
