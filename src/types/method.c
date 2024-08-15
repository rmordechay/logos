#include <stddef.h>
#include <stdlib.h>
#include "method.h"

/**
 *
 */
Method *create_method() {
    Method *method = malloc(sizeof(Method));
    method->identifier = NULL;
    return method;
}

/**
 *
 */
MethodBlock *create_method_block() {
    MethodBlock *method_block = malloc(sizeof(MethodBlock));
    method_block->name = NULL;
    method_block->methods = NULL;
    method_block->methods_len = 0;
    return method_block;
}

/**
 *
 */
void free_method(Method *method) {
    free_variable(method->identifier);
}

/**
 *
 */
void free_method_block(MethodBlock *method_block) {
    for (int i = 0; i < method_block->methods_len; i++) {
        free_method(method_block->methods[i]);
    }
}
