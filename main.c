#include <stdio.h>
//#include "gen/parser.h"

extern FILE *yyin;

extern int yyparse(void);
extern struct ASTNode *root;

void print_enum(int count, const char *enums_values[]) {
    for (int i = 0; i < count; i++) {

    }
}

int main() {
    const char * s[] = {
    "roi"
    };
    print_enum(1, s);
//    const char *filename = "lang/mylang.lng";
//    FILE *file;
//    file = fopen(filename, "r");
//    if (!file) {
//        fprintf(stderr, "Could not open file: %s\n", filename);
//        return 1;
//    }
//    yyin = file;
//    yyparse();
//    fclose(file);
    return 0;
}