#include <stdio.h>
#include "gen/parser.h"

extern FILE *yyin;
extern int yyparse(void);

int main() {
    const char *filename = "lang/main.lng";
    FILE *file;
    file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Could not open file: %s\n", filename);
        return 1;
    }
    yyin = file;
    yyparse();
    fclose(file);
    return 0;
}