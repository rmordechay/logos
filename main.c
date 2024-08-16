#include <stdio.h>
#include "gen/parser.h"
#include "ast/ast.h"
#include "analyser/analyser.h"
#include "project/project.h"

extern FILE *yyin;
extern int yyparse(void);
extern void yy_scan_string(const char *str);
extern void yy_delete_buffer(void *buffer);
struct Node *root;
void parse(const char *code);

int main() {
    init_project();
    return 0;
}

/**
 *
 */
void parse(const char *code) {
    yy_scan_string(code);
    yyparse();
    analyse_ast(root);
    yy_delete_buffer(yyin);
}


