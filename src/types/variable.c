#include <stddef.h>
#include <stdlib.h>
#include "variable.h"

/**
 *
 */
VariableDec *create_variable_declaration() {
    VariableDec *variable_declaration = malloc(sizeof(VariableDec));
    variable_declaration->variable_name = create_variable_name();
    variable_declaration->type = create_type();
    return variable_declaration;
}

/**
 *
 */
Variable *create_variable_name() {
    Variable *variable = malloc(sizeof(Variable));
    variable->name = NULL;
    return variable;
}

/**
 *
 */
void free_variable(VariableDec *variable) {
    free_type(variable->type);
    free(variable->variable_name);
    free(variable);
}
