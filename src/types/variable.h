#ifndef MYLANG_VARIABLE_H
#define MYLANG_VARIABLE_H

#include "type.h"

typedef struct Variable {
    char *name;
} Variable;

typedef struct VariableDeclaration {
    Variable *variable_name;
    Type *type;
} VariableDec;

VariableDec *create_variable_declaration();
Variable *create_variable_name();
void free_variable_declaration(VariableDec *variable);

#endif //MYLANG_VARIABLE_H
