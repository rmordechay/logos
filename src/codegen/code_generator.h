#ifndef LOGOS_CODE_GENERATOR_H
#define LOGOS_CODE_GENERATOR_H

#include "ast/tree.h"
#include "analyser/analysis.h"

typedef enum {
    STR,
    ADD,
    LOAD,
} CommandType;

typedef struct Command {
    CommandType command_type;
    void *p0;
    void *p1;
    struct Command *next_command;
} Command;

void generate_code(Command command, SymbolTable symbol_table);
Command create_command(CommandType command_type, void *p0, void *p1, struct Command *next_command);
void store_variable(SymbolTable symbolTable, const char *name, int value);
void add(SymbolTable symbol_table, char *left, char *right);
void load_variable(SymbolTable table, char *name);
void generate_print(LLVMValueRef value);

#endif //LOGOS_CODE_GENERATOR_H
