#include <stddef.h>
#include <stdlib.h>
#include "method.h"

/**
 *
 */
Method *create_method(Variable *variable) {
    Method *method = malloc(sizeof(Method));
    method->variable = variable;
    return method;
}

/**
 *
 */
void free_method(Method *method) {
    free_variable(method->variable);
}

/**
 *
 */
void free_method_block(MethodBlock *method_block) {
    for (int i = 0; i < method_block->methods_len; i++) {
        free_method(method_block->methods[i]);
    }
}
