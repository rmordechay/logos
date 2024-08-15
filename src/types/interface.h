#ifndef MYLANG_INTERFACE_H
#define MYLANG_INTERFACE_H

typedef struct Interface {
    char *name;
} Interface;

Interface *create_interface();
void free_interface(Interface *interface);

#endif //MYLANG_INTERFACE_H
