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
void analyse_object(ObjectEntity *entity) {

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
