#include <stdlib.h>
#include "types.h"

/**
 *
 */
Field *create_field() {
    Field *field = malloc(sizeof(Field));
    field->variable_dec = create_variable_declaration();
    field->interface = create_interface();
    return field;
}

/**
 *
 */
void free_field(Field *field) {
    free_variable_declaration(field->variable_dec);
    free(field);
}
