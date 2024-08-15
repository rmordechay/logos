#ifndef MYLANG_METHOD_H
#define MYLANG_METHOD_H

#include "type.h"
#include "variable.h"

typedef struct Method {
    Variable *variable;
} Method;

Method *create_method();
void free_method(Method *field);

#endif //MYLANG_METHOD_H
