#include <stdio.h>
#include "gen/parser.h"
#include "ast/ast.h"
#include "compiler/analyser.h"

extern FILE *yyin;
extern int yyparse(void);
struct Node *root;

int main() {
    const char *filename = "lang/mylang.lng";
    FILE *file;
    file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Could not open file: %s\n", filename);
        return 1;
    }
    yyin = file;
    yyparse();
    analyse_ast(root);
    fclose(file);
    return 0;
}