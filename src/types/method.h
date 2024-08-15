#ifndef MYLANG_METHOD_H
#define MYLANG_METHOD_H

#include "type.h"
#include "variable.h"
#include "statement.h"

typedef struct Method {
    VariableDec *var_dec;
    VariableDec **params;
    size_t params_len;
    Statement **statements;
    size_t statements_len;
} Method;

typedef struct MethodBlock {
    char *name;
    Method **methods;
    size_t methods_len;
} MethodBlock;

Method *create_method();
MethodBlock *create_method_block();
void free_method(Method *method);
void free_method_block(MethodBlock *method_block);

#endif //MYLANG_METHOD_H
