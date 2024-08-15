#ifndef MYLANG_OBJECT_H
#define MYLANG_OBJECT_H

#include "config.h"
#include "utils/utils.h"
#include "ast/ast.h"
#include "interface.h"
#include "field.h"
#include "method.h"

typedef struct Object {
    char *name;
    FileType file_type;
    Interface **interfaces;
    size_t interfaces_len;
    Field **fields;
    size_t fields_len;
    MethodBlock **method_blocks;
    size_t method_blocks_len;
} Object;

Object *create_object();
void free_object(Object *obj);
void print_obj(Object *obj);

#endif //MYLANG_OBJECT_H
