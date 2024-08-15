#ifndef MYLANG_VARIABLE_H
#define MYLANG_VARIABLE_H

#include "type.h"

typedef struct Variable {
    char *name;
    Type *type;
} Variable;

Variable *create_variable();
void free_variable(Variable *variable);

#endif //MYLANG_VARIABLE_H
