#ifndef MYLANG_FIELD_H
#define MYLANG_FIELD_H

#include "variable.h"
#include "type.h"

typedef struct Field {
    Type *type;
    Variable *variable;
} Field;

#endif //MYLANG_FIELD_H
