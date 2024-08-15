#ifndef MYLANG_OBJECT_H
#define MYLANG_OBJECT_H

#include "config.h"
#include "utils/utils.h"
#include "ast/ast.h"
#include "interface.h"

typedef struct Object {
    char *name;
    FileType fileType;
    Interface **interfaces;
    size_t interfaces_len;
} Object;

Object *create_object();
void free_object(Object *obj);
void print_obj(Object *obj);

#endif //MYLANG_OBJECT_H
