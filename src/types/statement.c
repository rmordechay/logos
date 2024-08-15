#include <stdlib.h>
#include "types.h"


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
