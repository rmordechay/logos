#include <stdlib.h>
#include "statement.h"


/**
 *
 */
Statement *create_statement() {
    Statement *stmt = malloc(sizeof(Statement));
    return stmt;
}

/**
 *
 */
void free_statement(Statement *stmt) {
    free(stmt);
}
