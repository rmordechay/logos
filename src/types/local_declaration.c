#include <stdlib.h>
#include "types.h"

/**
 *
 */
LocalDec *create_local_declaration() {
    LocalDec *local_dec = malloc(sizeof(LocalDec));
    local_dec->variable_dec = create_variable_declaration();
    local_dec->expr = NULL;
    return local_dec;
}

/**
 *
 */
void free_local_declaration(LocalDec *local_dec) {
    free_variable_declaration(local_dec->variable_dec);
    free_expr(local_dec->expr);
}
