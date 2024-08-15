#include <stdlib.h>
#include "object.h"

/**
 *
 */
Object *create_object() {
    Object *obj = malloc(sizeof(Object));
    obj->name = NULL;
    obj->fileType = OBJECT_FILE;
    obj->interfaces = NULL;
    obj->interfaces_len = 0;
    return obj;
}

/**
 *
 */
void free_object(Object *obj) {
    if (obj) {
        free(obj->name);
        for (size_t i = 0; i < obj->interfaces_len; i++) {
            free(obj->interfaces[i]->name);
            free(obj->interfaces[i]);
        }
        free(obj->interfaces);
        free(obj);
    }
}

/**
*
*/
void print_obj(Object *obj) {
    printf("Name: %s\n", obj->name);
    for (size_t i = 0; i < obj->interfaces_len; i++) {
        printf("Interface %zu: %s\n", i + 1, obj->interfaces[i]->name);
    }
}