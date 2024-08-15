#ifndef MYLANG_METHOD_H
#define MYLANG_METHOD_H

#include "type.h"
#include "variable.h"

typedef struct Method {
    VariableDeclaration *variable_declaration;
    VariableDeclaration **params;
    size_t params_len;
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
