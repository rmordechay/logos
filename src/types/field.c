#include <stdlib.h>
#include "field.h"

/**
 *
 */
Field *create_field() {
    Field *field = malloc(sizeof(Field));
    field->variable = create_variable();
    field->interface = create_interface();
    return field;
}

/**
 *
 */
void free_field(Field *field) {
    free_variable(field->variable);
    free(field);
}
