#include <stddef.h>
#include <stdlib.h>
#include "type.h"

/**
 *
 */
Type *create_type() {
    Type *type = malloc(sizeof(Type));
    type->name = NULL;
    return type;
}

/**
 *
 */
void free_type(Type *type) {
    free(type->name);
    free(type);
}
