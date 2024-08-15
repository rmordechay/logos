#include <stddef.h>
#include <stdlib.h>
#include "types.h"

/**
 *
 */
Method *create_method() {
    Method *method = malloc(sizeof(Method));
    method->var_dec = create_variable_declaration();
    method->statements_len = 0;
    method->statements = NULL;
    method->params_len = 0;
    method->params = NULL;
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
    free_variable_declaration(method->var_dec);
    for (int i = 0; i < method->params_len; i++) {
        free_variable_declaration(method->params[i]);
    }
    for (int i = 0; i < method->statements_len; i++) {
        free_statement(method->statements[i]);
    }
}

/**
 *
 */
void free_method_block(MethodBlock *method_block) {
    free(method_block->name);
    for (int i = 0; i < method_block->methods_len; i++) {
        free_method(method_block->methods[i]);
    }
}
