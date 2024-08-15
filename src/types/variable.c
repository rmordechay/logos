#include <stddef.h>
#include <stdlib.h>
#include "variable.h"

/**
 *
 */
VariableDeclaration *create_variable_declaration() {
    VariableDeclaration *variable_declaration = malloc(sizeof(VariableDeclaration));
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
void free_variable(VariableDeclaration *variable) {
    free_type(variable->type);
    free(variable->variable_name);
    free(variable);
}
