#include <stdlib.h>
#include "object.h"

/**
 *
 */
Object *create_object() {
    Object *obj = malloc(sizeof(Object));
    obj->name = NULL;
    obj->file_type = OBJECT_FILE;
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

        }
        for (size_t i = 0; i < obj->fields_len; i++) {

        }
        for (size_t i = 0; i < obj->interfaces_len; i++) {

        }
        free(obj->interfaces);
        free(obj);
    }
}

