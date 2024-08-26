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
void add_error(int error_code, char *message) {
    struct Error err;
    err.error_code = error_code;
    err.message = message;
    errors[err_count] = err;
    err_count++;
}


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
    ImplementsBlock *implements_block = entity->implements_block;
    ObjFieldList *field_list = entity->field_list;
    ObjMethodsBlockList *methods_block_list = entity->methods_block_list;
    check_object_implementations(implements_block->type_list, methods_block_list);
    check_field_implementations(implements_block->type_list, field_list);
}

/**
 *
 */
void analyse_interface(InterfaceEntity *entity) {}

/**
 * 
 */
void check_field_implementations(TypeList *implements_types, ObjFieldList *field_list) {
    for (int i = 0; i < field_list->count; i++) {
        Type *implements_type = field_list->fields[i]->implements;
        if (implements_type == NULL) continue;
        if (!is_name_in_type_list(implements_types, implements_type->name)) {
            add_error(OBJECT_DOES_NOT_IMPLEMENT_INTERFACE);
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
void check_object_implementations(TypeList *implements_types, ObjMethodsBlockList *methods_block_list) {
    for (int i = 0; i < methods_block_list->count; i++) {
        char *block_name = methods_block_list->blocks[i]->identifier->name;
        if (strcmp(block_name, SELF_CLASS) == 0) continue;
        if (!is_name_in_type_list(implements_types, block_name)) {
            add_error(OBJECT_DOES_NOT_IMPLEMENT_INTERFACE);
            break;
        }
    }
}

/**
 *
 */
void print_errors() {
    for (int i = 0; i < err_count; i++) {
        Error err = errors[i];
        printf("%s (%i)\n", err.message, err.error_code);
    }
}
