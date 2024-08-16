#include <stdio.h>
#include "gen/parser.h"
#include "ast/ast.h"
#include "analyser/analyser.h"
#include "project/project.h"

extern FILE *yyin;
extern int yyparse(void);
struct Node *root;
void parse();

int main() {
    init_project();
    return 0;
}

/**
 *
 */
void parse() {
    const char *filename = "lang/src/object.lgs";
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Could not open file: %s\n", filename);
        return;
    }
    yyin = file;
    yyparse();
    analyse_ast(root);
    fclose(file);
}


