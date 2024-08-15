#include <stdlib.h>
#include "object.h"
#include "method.h"

/**
 *
 */
Object *create_object() {
    Object *obj = malloc(sizeof(Object));
    obj->name = NULL;
    obj->file_type = OBJECT_FILE;
    obj->interfaces = NULL;
    obj->interfaces_len = 0;
    obj->fields = NULL;
    obj->fields_len = 0;
    obj->method_blocks = NULL;
    obj->method_blocks_len = 0;
    return obj;
}

/**
 *
 */
void free_object(Object *obj) {
    if (obj) {
        for (size_t i = 0; i < obj->interfaces_len; i++) {
            free_interface(obj->interfaces[i]);
        }
        for (size_t i = 0; i < obj->fields_len; i++) {
            free_field(obj->fields[i]);
        }
        for (size_t i = 0; i < obj->method_blocks_len; i++) {
            free_method_block(obj->method_blocks[i]);
        }
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
    for (size_t i = 0; i < obj->fields_len; i++) {
        printf("Field %zu: %s %s\n", i + 1, obj->fields[i]->variable->name, obj->fields[i]->variable->type->name);
    }
}