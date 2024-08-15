#include <stdlib.h>
#include "interface.h"

/**
 *
 */
Interface *create_interface() {
    Interface *interface = malloc(sizeof(Interface));
    interface->name = NULL;
    return interface;
}

/**
 *
 */
void free_interface(Interface *interface) {
    free(interface->name);
    free(interface);
}
