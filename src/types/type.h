#ifndef MYLANG_TYPE_H
#define MYLANG_TYPE_H

typedef struct Type {
    char *name;
} Type;

Type *create_type();
void free_type(Type *type);

#endif //MYLANG_TYPE_H
