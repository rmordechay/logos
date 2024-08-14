#include <stdio.h>
#include "gen/parser.h"
#include "ast/ast.h"

extern FILE *yyin;
extern int yyparse(void);
struct ASTNode *root;

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
    print_node(root, 0);
    fclose(file);
    return 0;
}