#ifndef MYLANG_LOCAL_DECLARATION_H
#define MYLANG_LOCAL_DECLARATION_H

#include "type.h"
#include "variable.h"
#include "expr.h"

typedef struct LocalDeclaration {
    VariableDec *variable_dec;
    Expr *expr;
} LocalDec;

LocalDec *create_local_declaration();
void free_local_declaration(LocalDec *local_dec);

#endif //MYLANG_LOCAL_DECLARATION_H
