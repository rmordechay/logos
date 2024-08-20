#include <printf.h>
#include <strings.h>
#include "object_analyser.h"
#include "ast/tree.h"
#include "executor/executor.h"

char errors[1024][1024];
int err_count = 0;

void print_error(char *msg);
void check_fields_implementation(TypeList *implements_types, FieldList *field_list);
void check_methods_implementation(TypeList *implements_types, MethodsBlockList *methods_block_list);
void check_implementation(ObjectEntity *entity);

/**
 *
 */
void analyse_object(ObjectEntity *entity) {
    execute(entity);
}

/**
 *
 */
void check_implementation(ObjectEntity *entity) {
    FieldList *field_list = entity->fields_block->field_list;
    TypeList *implements_type = entity->implements_block->type_list;
    MethodsBlockList *methods_block_list = entity->methods_block_list;
    check_fields_implementation(implements_type, field_list);
    check_methods_implementation(implements_type, methods_block_list);
}

/**
 *
 */
void check_fields_implementation(TypeList *implements_types, FieldList *field_list) {

}

/**
 *
 */
void check_methods_implementation(TypeList *implements_types, MethodsBlockList *methods_block_list) {

}

/**
 *
 */
void print_error(char *msg) {
    strcpy(errors[err_count], msg);
    err_count++;
    printf("%s\n", msg);
}
