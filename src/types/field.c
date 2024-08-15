#include <stdlib.h>
#include "field.h"

/**
 *
 */
Field *create_field() {
    Field *field = malloc(sizeof(Field));
    field->variable_declaration = create_variable_declaration();
    field->interface = create_interface();
    return field;
}

/**
 *
 */
void free_field(Field *field) {
    free_variable(field->variable_declaration);
    free(field);
}
