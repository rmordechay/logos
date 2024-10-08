#include <printf.h>
#include "ast/tree.h"
#include "errors.h"
#include "project/project.h"
#include "analysis.h"
#include <string.h>
#include "codegen/code_generator.h"


#define SELF_CLASS "Self"
#define SELF_VARIABLE "self"

Error errors[MAX_ERRORS];
int err_count = 0;

FILE *yyin;
Entity *root;
int yyparse(void);
void yy_scan_string(const char *str);
void yy_delete_buffer(void *buffer);
void parse(const char *code);
void print_errors();


void print_symbols();

/**
 *
 */
void parse(const char *code) {
    yy_scan_string(code);
    yyparse();
    yy_delete_buffer(yyin);
}

SymbolTable symbol_table;
Command current_cmd;

/**
 *
 */
void parse_file(const AppFile *app_file) {
    parse(app_file->code);
    switch (root->type) {
        case E_OBJECT:
            analyse_object(root->object_entity);
            long *a = malloc(sizeof(int));
            long *b = malloc(sizeof(int));
            *a = 4;
            *b = 12;
            char *name_a = "a";
            char *name_b = "b";
            Command cmd5 = create_command(ADD, name_a, name_b, NULL);
            Command cmd4 = create_command(LOAD, name_b, NULL, &cmd5);
            Command cmd3 = create_command(LOAD, name_b, NULL, &cmd4);
            Command cmd2 = create_command(STR, name_b, b, &cmd3);
            Command cmd1 = create_command(STR, name_a, a, &cmd2);
            generate_code(cmd1, symbol_table);
            break;
        case E_INTERFACE:
            analyse_interface(root->interface_entity);
            break;
        case E_ENUM:
            break;
    }
}

/**
 *
 */
void analyse_src_code(App *app) {
    symbol_table.symbols = create_hash_map();
    Package *src_pkg = get_from_map(app->packages, SRC_DIR)->package;
    for (int i = 0; i < TABLE_SIZE; i++) {
        KeyValue *pair = src_pkg->files->table[i];
        if (pair == NULL) continue;
        AppFile *app_file = pair->file;
        parse_file(app_file);
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
    check_field_implementations(implements_block->type_list, field_list, obj_name);
    check_method_implementations(implements_block->type_list, methods_block_list, obj_name);
    check_methods_blocks(methods_block_list);
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
            add_error(OBJECT_FIELD_DOES_NOT_IMPLEMENT_INTERFACE_CODE, err_msg);
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
            add_error(OBJECT_DOES_NOT_IMPLEMENT_INTERFACE_CODE, err_msg);
            break;
        }
    }
}


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
void check_methods_blocks(ObjMethodsBlockList *methods_block_list) {
    for (int i = 0; i < methods_block_list->count; i++) {
        ObjMethodsBlock *block = methods_block_list->blocks[i];
        for (int j = 0; j < block->methods_list->count; j++) {
            ObjMethod *method = block->methods_list->methods[j];
            check_method(method);
        }
    }
}

/**
 *
 */
void check_method(ObjMethod *method) {
    StatementList *statement_list = method->statement_list;
    for (int i = 0; i < statement_list->count; i++) {
        Statement *statement = statement_list->statements[i];
        check_statement(statement);
    }
}

/**
 *
 */
void check_statement(Statement *stmt) {
    switch (stmt->type) {
        case ST_LOCAL_DECLARATION:
            check_local_declaration(stmt->local_declaration);
            break;
        case ST_IF_STATEMENT:
            check_if_statement(stmt->if_statement);
            break;
        case ST_PATTERN_MATCHING:
            check_pattern_matching(stmt->pattern_matching);
            break;
        case ST_PATTERN_MATCHING_EXPR:
            check_pattern_matching_expr(stmt->pattern_matching_expr);
            break;
        case ST_ITERATION:
            check_iteration(stmt->iteration);
            break;
        case ST_RETURN_STATEMENT:
            check_return_statement(stmt->return_statement);
            break;
        case ST_BREAK_STATEMENT:
            check_break_statement(stmt->break_expr);
            break;
        case ST_CONTINUE_STATEMENT:
            check_continue_statement();
            break;
        case ST_ENUM_STATEMENT:
            check_enum_statement(stmt->enum_declaration);
            break;
        case ST_EXPR:
            check_expr(stmt->expr);
            break;
    }
}

/**
 *
 */
Type infer_type(Expr *expr) {
    Type type = {.name = NULL};
    return type;
}

/**
 *
 */
void check_local_declaration(LocalDeclaration *local_declaration) {
    char *type;
    if (local_declaration->type == NULL) {
        type = infer_type(local_declaration->expr).name;
    } else {
        type = local_declaration->type->name;
    }
    add_symbol(local_declaration->identifier->name, type, S_VARIABLE);
}

/**
 *
 */
void check_if_statement(IfStatement *if_statement) {

}

/**
 *
 */
void check_pattern_matching(PatternMatching *pattern_matching) {

}

/**
 *
 */
void check_pattern_matching_expr(PatternMatchingExpr *pattern_matching_expr) {

}

/**
 *
 */
void check_iteration(Iteration *iteration) {

}

/**
 *
 */
void check_return_statement(ReturnStatement *return_statement) {

}

/**
 *
 */
void check_break_statement(Expr *break_expr) {

}

/**
 *
 */
void check_continue_statement() {

}

/**
 *
 */
void check_enum_statement(EnumDeclaration *enum_declaration) {

}

/**
 *
 */
void check_expr(Expr *expr) {
    switch (expr->type) {
        case E_UNARY:
            check_unary_expr(expr->unary_expr);
            break;
        case E_BINARY:
            check_binary_expr(expr->binary_expr);
            break;
    }
}


/**
 *
 */
void check_unary_expr(UnaryExpr *expr) {
    switch (expr->type) {
        case UE_INT:
            break;
        case UE_FLOAT:
            break;
        case UE_BOOL:
            break;
        case UE_STRING:
            break;
        case UE_IDENTIFIER:
            break;
        case UE_METHOD_CALL:
            check_method_call(expr->method_call);
            break;
        case UE_COLLECTION:
            break;
    }
}

/**
 *
 */
void check_method_call(MethodCall *method_call) {

}

/**
 *
 */
void check_binary_expr(BinaryExpr *expr) {

}

/**
 *
 */
void add_symbol(char *id_name, char* type_name, SymbolType symbol_type) {
    Symbol *symbol = malloc(sizeof(Symbol));
    symbol->name = strdup(id_name);
    symbol->type = strdup(type_name);
    symbol->symbolType = symbol_type;
    put_in_map(symbol_table.symbols, strdup(id_name), symbol);
}

/**
 *
 */

void print_symbols() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        KeyValue *p_value = symbol_table.symbols->table[i];
        if (p_value == NULL) continue;
        Symbol *value = p_value->symbol;
    }
}

/**
 *
 */
void free_symbol(Symbol *s) {
    free(s);
}

/**
 *
 */
void free_symbol_table(SymbolTable *st) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if(st->symbols->table[i] == NULL) continue;
    }
}

/**
 *
 */
void add_error(int error_code, char *message) {
    struct Error err;
    err.error_code = error_code;
    err.message = strdup(message);
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
        printf("%i: (%i) %s\n", err.error_count, err.error_code, err.message);
    }
}
