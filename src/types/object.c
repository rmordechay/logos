#include <stdlib.h>
#include "types.h"

/**
 *
 */
Object *create_object() {
    Object *obj = malloc(sizeof(Object));
    obj->name = NULL;
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
    printf("Name:\n\t%s\n", obj->name);
    printf("Interfaces:\n");
    for (size_t i = 0; i < obj->interfaces_len; i++) {
        printf("\t%s\n", obj->interfaces[i]->name);
    }
    printf("Fields:\n");
    for (size_t i = 0; i < obj->fields_len; i++) {
        printf("\t%s %s\n", obj->fields[i]->variable_dec->type->name, obj->fields[i]->variable_dec->variable_name->name);
    }
    printf("Method Blocks:\n");
    for (size_t i = 0; i < obj->method_blocks_len; i++) {
        MethodBlock *method_block = obj->method_blocks[i];
        printf("\t%s:\n", method_block->name);
        for (size_t j = 0; j < method_block->methods_len; j++) {
            Method *method = method_block->methods[j];
            printf("\t\t%s %s() ", method->var_dec->type->name, method->var_dec->variable_name->name);
            for (int k = 0; k < method->params_len; k++) {
                VariableDec *vd = method->params[k];
                printf("%s %s ", vd->variable_name->name, vd->type->name);
            }
            printf("\n");
        }
    }
}