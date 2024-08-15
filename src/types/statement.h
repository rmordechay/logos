#ifndef MYLANG_STATEMENT_H
#define MYLANG_STATEMENT_H

#include "local_declaration.h"

typedef struct Statement {
    LocalDec *local_dec;
} Statement;

Statement *create_statement();
void free_statement(Statement *stmt);

#endif //MYLANG_STATEMENT_H
