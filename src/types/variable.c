#include <stddef.h>
#include <stdlib.h>
#include "variable.h"

/**
 *
 */
Variable *create_variable() {
    Variable *variable = malloc(sizeof(Variable));
    variable->name = NULL;
    variable->type = create_type();
    return variable;
}

/**
 *
 */
void free_variable(Variable *variable) {
    free_type(variable->type);
    free(variable->name);
    free(variable);
}
