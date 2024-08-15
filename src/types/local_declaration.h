#ifndef MYLANG_LOCAL_DECLARATION_H
#define MYLANG_LOCAL_DECLARATION_H

#include "type.h"

typedef struct LocalDeclaration {
    Type *name;
    Type *type;
} LocalDec;

#endif //MYLANG_LOCAL_DECLARATION_H
