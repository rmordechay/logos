#include <stdlib.h>
#include "statement.h"


/**
 *
 */
Statement *create_statement() {
    Statement *stmt = malloc(sizeof(Statement));
    stmt->local_dec = NULL;
    return stmt;
}

/**
 *
 */
void free_statement(Statement *stmt) {
    if (stmt->local_dec != NULL) {
        free_local_declaration(stmt->local_dec);
    }
    free(stmt);
}
