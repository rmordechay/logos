#ifndef LOGOS_ANALYSIS_H
#define LOGOS_ANALYSIS_H

#include "ast/tree.h"
#include "project/project.h"
#include "project/project.h"
#include <stdbool.h>

void analyse_object(ObjectEntity *entity);
void analyse_interface(InterfaceEntity *entity);
void analyse_tree(App *app);

void check_method_implementations(TypeList *implements_types, ObjMethodsBlockList *methods_block_list, char *obj_name);
void check_field_implementations(TypeList *implements_types, ObjFieldList *field_list, char *obj_name);
bool is_name_in_type_list(const TypeList *type_list, const char *name);
#endif //LOGOS_ANALYSIS_H
