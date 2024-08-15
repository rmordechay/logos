#ifndef MYLANG_FIELD_H
#define MYLANG_FIELD_H

#include "variable.h"
#include "type.h"
#include "interface.h"

typedef struct Field {
    VariableDeclaration *variable_declaration;
    Interface *interface;
} Field;

Field *create_field();
void free_field(Field *field);

#endif //MYLANG_FIELD_H
