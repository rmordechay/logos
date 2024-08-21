#ifndef LOGOS_OBJECT_ANALYSER_H
#define LOGOS_OBJECT_ANALYSER_H

#include "ast/tree.h"

void analyse_object(ObjectEntity *entity);
void print_error(char *msg);
void check_fields_implementation(TypeList *implements_types, ObjectFieldList *field_list);
void check_methods_block_implementation(TypeList *implements_types, ObjectMethodsBlockList *methods_block_list);
void check_implementations(ObjectEntity *entity);

#endif //LOGOS_OBJECT_ANALYSER_H
