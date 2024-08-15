#ifndef MYLANG_FIELD_H
#define MYLANG_FIELD_H

#include "variable.h"
#include "type.h"
#include "interface.h"

typedef struct Field {
    Type *type;
    Variable *variable;
    Interface *Interface;
} Field;

#endif //MYLANG_FIELD_H
