#include <printf.h>
#include "ast/tree.h"
#include "errors.h"
#include "project/project.h"
#include "object_analyser.h"


#define MAX_ERRORS 1000

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
}

/**
 *
 */
typedef struct LgsScopeVariable {
    Type type;
    Identifier identifier;
    char *value;
} Lgs_ScopeVariable;

/**
 *
 */
typedef struct Scope {
    HashMap identifiers;
} Lgs_Scope;


/**
 *
 */
Type *infer_type(Expr *expr) {
    switch (expr->type) {
        case E_UNARY:
        case E_BINARY:
            break;
    }
    return NULL;
}

/**
 *
 */
Lgs_Scope get_scope() {
    HashMap hash_map;
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_map.table[i] = NULL;
    }
    Lgs_Scope scope;
    scope.identifiers = hash_map;
    return scope;
}

/**
 *
 */
void visit_local_dec(Statement *statement, Lgs_Scope *scope) {
    LocalDeclaration *declaration = statement->local_declaration;
    Identifier *identifier = declaration->identifier;
    Type *type = declaration->type;
    Lgs_ScopeVariable var_dec;
    var_dec.type = *type;
    var_dec.identifier = *identifier;
    put_in_map(&(*scope).identifiers, identifier->name, &var_dec);
}

/**
 *
 */
Lgs_Scope visit_statement(Statement *statement, Lgs_Scope scope) {
    switch (statement->type) {
        case ST_LOCAL_DECLARATION:
            visit_local_dec(statement, &scope);
            break;
        case ST_IF_STATEMENT:
            break;
        case ST_PATTERN_MATCHING:
            break;
        case ST_PATTERN_MATCHING_EXPR:
            break;
        case ST_ITERATION:
            break;
        case ST_RETURN_STATEMENT:
            break;
        case ST_BREAK_STATEMENT:
            break;
        case ST_CONTINUE_STATEMENT:
            break;
        case ST_ENUM_STATEMENT:
            break;
    }
    return scope;
}

/**
 *
 */
void visit_scope(StatementList *statement_list) {
    Lgs_Scope scope = get_scope();
    for (int i = 0; i < statement_list->count; i++) {
        Statement *statement = statement_list->statements[i];
        scope = visit_statement(statement, scope);
    }
}

/**
 *
 */
void analyse_object(ObjectEntity *entity) {
    ObjMethodsBlockList *methods_block_list = entity->methods_block_list;
    ObjFieldList *field_list = entity->field_list;
    ImplementsBlock *implements_block = entity->implements_block;
    ObjectMethod *method = methods_block_list->blocks[0]->methods_list->methods[0];
    visit_scope(method->statement_list);
}

/**
 * 
 */
void analyse_interface(InterfaceEntity *entity) {

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
