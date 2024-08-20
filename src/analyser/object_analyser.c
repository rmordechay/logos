#include <printf.h>
#include <strings.h>
#include "object_analyser.h"
#include "ast/tree.h"
#include "errors.h"

#define MAX_ERRORS 1000

Error errors[MAX_ERRORS];
int err_count = 0;

/**
 *
 */
void analyse_object(ObjectEntity *entity) {
    check_implementations(entity);
    for (int i = 0; i < err_count; i++) {
        Error err = errors[i];
        printf("%s (%i)\n", err.message, err.error_code);
    }
}

/**
 *
 */
void check_implementations(ObjectEntity *entity) {
    FieldList *field_list = entity->fields_block->field_list;
    TypeList *implements_type = entity->implements_block->type_list;
    MethodsBlockList *methods_block_list = entity->methods_block_list;
    check_fields_implementation(implements_type, field_list);
    check_methods_block_implementation(implements_type, methods_block_list);
}

/**
 *
 */
void check_fields_implementation(TypeList *implements_types, FieldList *field_list) {
    for (int i = 0; i < implements_types->count; i++) {
        char *type_name = implements_types->types[i]->name;
        for (int j = 0; j < field_list->count; j++) {
            Field *field = field_list->fields[j];
            Type *implement_type = field->implements;
            if (implement_type == NULL || strcmp(type_name, implement_type->name) == 0) {
                continue;
            } else {
                errors[err_count++] = create_error(ERR_FIELDS_NOT_IMPLEMENTED);
            }
        }
    }
}

/**
 *
 */
void check_methods_block_implementation(TypeList *implements_types, MethodsBlockList *methods_block_list) {

}
