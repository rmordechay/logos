#include <stdio.h>
#include "gen/parser.h"
#include "ast/ast.h"
#include "analyser/analyser.h"

extern FILE *yyin;
extern int yyparse(void);
struct Node *root;

int main() {
    const char *filename = "lang/object.lng";
    FILE *file;
    file = fopen(filename, "r");
    yyin = file;
    yyparse();
    analyse_ast(root);
    fclose(file);
    return 0;
}