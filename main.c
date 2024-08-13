#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include "gen/parser.h"

extern FILE *yyin;

extern int yyparse(void);

extern struct ASTNode *root;

void print_enum_definition(int count, ...) {
    va_list args;
    va_start(args, count);
    printf("typedef enum {\n");
    for (int i = 0; i < count; i++) {
        char *str = va_arg(args, char*);
        char enum_str[100] = "N_";
        strcat(enum_str, str);
        for (int j = 0; enum_str[j] != '\0'; j++) {
            enum_str[j] = (char) toupper(enum_str[j]);
        }
        printf("    %s,\n", enum_str);
    }
    printf("} NodeType;\n");
    va_end(args);
}

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
    fclose(file);
    return 0;
}