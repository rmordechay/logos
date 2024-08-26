#include <printf.h>
#include "ast/tree.h"
#include "errors.h"
#include "project/project.h"
#include "analysis.h"
#include <string.h>

#define SELF_CLASS "Self"
#define SELF_VARIABLE "self"

Error errors[MAX_ERRORS];
int err_count = 0;

extern FILE *yyin;
extern int yyparse(void);
extern void yy_scan_string(const char *str);
extern void yy_delete_buffer(void *buffer);
void parse(const char *code);
void print_errors();

/**
 *
 */
void parse(const char *code) {
    yy_scan_string(code);
    yyparse();
    yy_delete_buffer(yyin);
}


/**
 *
 */
void analyse_tree(App *app) {
    Package *src_pkg = get_from_map(app->packages, SRC_DIR)->package;
    for (int i = 0; i < TABLE_SIZE; i++) {
        KeyValue *pair = src_pkg->files->table[i];
        if (pair == NULL) continue;
        AppFile *app_file = pair->file;
        parse(app_file->code);
    }
    print_errors();
}

/**
 *
 */
void analyse_object(ObjectEntity *entity) {
    char *obj_name = entity->id->name;
    ImplementsBlock *implements_block = entity->implements_block;
    ObjFieldList *field_list = entity->field_list;
    ObjMethodsBlockList *methods_block_list = entity->methods_block_list;
    check_method_implementations(implements_block->type_list, methods_block_list, obj_name);
    check_field_implementations(implements_block->type_list, field_list, obj_name);
}


/**
 *
 */
void analyse_interface(InterfaceEntity *entity) {}

/**
 *
 */
void check_field_implementations(TypeList *implements_types, ObjFieldList *field_list, char *obj_name) {
    for (int i = 0; i < field_list->count; i++) {
        ObjectField *field = field_list->fields[i];
        char *field_name = field->variable_declaration->identifier->name;
        Type *implements_type = field->implements;
        if (implements_type == NULL) continue;
        if (!is_name_in_type_list(implements_types, implements_type->name)) {
            char err_msg[MAX_ERROR_MSG_SIZE];
            snprintf(err_msg, sizeof(err_msg), OBJECT_FIELD_DOES_NOT_IMPLEMENT_INTERFACE_MSG, field_name, obj_name, implements_type->name);
            add_error(OBJECT_FIELD_DOES_NOT_IMPLEMENT_INTERFACE_CODE, err_msg, implements_type->line_number);
            break;
        }
    }
}

/**
*
*/
void check_method_implementations(TypeList *implements_types, ObjMethodsBlockList *methods_block_list, char *obj_name) {
    for (int i = 0; i < methods_block_list->count; i++) {
        Type *identifier = methods_block_list->blocks[i]->identifier;
        char *block_name = identifier->name;
        if (strcmp(block_name, SELF_CLASS) == 0) continue;
        if (!is_name_in_type_list(implements_types, block_name)) {
            char err_msg[MAX_ERROR_MSG_SIZE];
            snprintf(err_msg, sizeof(err_msg), OBJECT_DOES_NOT_IMPLEMENT_INTERFACE_MSG, obj_name, block_name);
            add_error(OBJECT_DOES_NOT_IMPLEMENT_INTERFACE_CODE, err_msg, identifier->line_number);
            break;
        }
    }
}


/**
 *
 */

bool is_name_in_type_list(const TypeList *type_list, const char *name) {
    for (int i = 0; i < type_list->count; i++) {
        char *implement_name = type_list->types[i]->name;
        if (strcmp(name, implement_name) == 0) {
            return true;
        }
    }
    return false;
}
/**
 *
 */
void add_error(int error_code, char *message, int line_number) {
    struct Error err;
    err.error_code = error_code;
    err.message = message;
    err.line_number = line_number;
    err.error_count = err_count;
    errors[err_count] = err;
    err_count++;
}

/**
 *
 */
void print_errors() {
    for (int i = 0; i < err_count; i++) {
        Error err = errors[i];
        printf("%i: (%i) %s : line %i\n", err.error_count, err.error_code, err.message, err.line_number);
    }
}
