#ifndef MYLANG_METHOD_H
#define MYLANG_METHOD_H

#include "type.h"
#include "variable.h"

typedef struct Method {
    char *name;
    Variable *variable;
} Method;

typedef struct MethodBlock {
    Method **methods;
    size_t methods_len;
} MethodBlock;

Method *create_method(Variable *variable);
void free_method(Method *method);
void free_method_block(MethodBlock *method_block);

#endif //MYLANG_METHOD_H
