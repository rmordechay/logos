#ifndef LOGOS_ANALYSIS_H
#define LOGOS_ANALYSIS_H

#include "ast/tree.h"
#include "project/project.h"
#include "project/project.h"
#include <stdbool.h>

void analyse_object(ObjEntity *entity);
void analyse_interface(InterfaceEntity *entity);
void analyse_tree(App *app);

void check_method_implementations(TypeList *implements_types, ObjMethodsBlockList *methods_block_list, char *obj_name);
void check_field_implementations(TypeList *implements_types, ObjFieldList *field_list, char *obj_name);
void check_methods_blocks(ObjMethodsBlockList *methods_block_list);
void check_method(ObjMethod *method);

void check_local_declaration(LocalDeclaration *local_declaration);
void check_if_statement(IfStatement *if_statement);
void check_pattern_matching(PatternMatching *pattern_matching);
void check_pattern_matching_expr(PatternMatchingExpr *pattern_matching_expr);
void check_iteration(Iteration *iteration);
void check_return_statement(ReturnStatement *return_statement);
void check_break_statement(Expr *break_expr);
void check_continue_statement();
void check_enum_statement(EnumDeclaration *enum_declaration);
void check_expr(Expr *expr);

bool is_name_in_type_list(const TypeList *type_list, const char *name);

#endif //LOGOS_ANALYSIS_H
