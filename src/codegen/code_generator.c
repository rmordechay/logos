#include <llvm-c/Core.h>
#include <stddef.h>
#include <string.h>
#include "code_generator.h"


#define EMPTY_NAME ""

LLVMModuleRef module;
LLVMBuilderRef builder;

void generate_code(Command command, SymbolTable symbol_table) {
    module = LLVMModuleCreateWithName("module");
    builder = LLVMCreateBuilder();
    LLVMTypeRef main_func_type = LLVMFunctionType(LLVMInt32Type(), NULL, 0, 0);
    LLVMValueRef main_func = LLVMAddFunction(module, "main", main_func_type);
    LLVMBasicBlockRef entry_block = LLVMAppendBasicBlock(main_func, "entry_block");
    LLVMPositionBuilderAtEnd(builder, entry_block);

    Command cmd = command;
    for (;;) {
        switch (cmd.command_type) {
            case STR:
                store_variable(symbol_table, cmd.p0, *((int *) cmd.p1));
                break;
            case ADD:
                add(symbol_table, cmd.p0, cmd.p1);
                break;
            case LOAD:
                load_variable(symbol_table, cmd.p0);
                break;
        }
        if (cmd.next_command == NULL) break;
        cmd = *cmd.next_command;
    }

    LLVMBuildRet(builder, LLVMConstInt(LLVMInt32Type(), 0, 0));
    LLVMDumpModule(module);
    LLVMPrintModuleToFile(module, "output.ll", NULL);

    LLVMDisposeBuilder(builder);
    LLVMDisposeModule(module);
}

/**
 *
 */
void store_variable(SymbolTable symbolTable, const char *name, int value) {
    LLVMValueRef ptr = LLVMBuildAlloca(builder, LLVMInt32Type(), name);
    LLVMValueRef val = LLVMConstInt(LLVMInt32Type(), value, false);
    LLVMBuildStore(builder, val, ptr);
    Symbol *symbol = get_from_map(symbolTable.symbols, name)->symbol;
    symbol->ptr = ptr;
}

/**
 *
 */
void load_variable(SymbolTable symbol_table, char *name) {}

/**
 *
 */
void add(SymbolTable symbol_table, char *left, char *right) {
    Symbol *l = get_from_map(symbol_table.symbols, left)->symbol;
    Symbol *r = get_from_map(symbol_table.symbols, right)->symbol;
    LLVMValueRef load_var_l = LLVMBuildLoad2(builder, LLVMInt32Type(), l->ptr, EMPTY_NAME);
    LLVMValueRef load_var_r = LLVMBuildLoad2(builder, LLVMInt32Type(), r->ptr, EMPTY_NAME);
    LLVMValueRef sum = LLVMBuildAdd(builder, load_var_l, load_var_r, EMPTY_NAME);
    LLVMValueRef ptr = LLVMBuildAlloca(builder, LLVMInt32Type(), EMPTY_NAME);
    LLVMBuildStore(builder, sum, ptr);
    LLVMValueRef load_sum = LLVMBuildLoad2(builder, LLVMInt32Type(), ptr, EMPTY_NAME);
    generate_print(load_sum);
}

/**
 *
 */
Command create_command(CommandType command_type, void *p0, void *p1, struct Command *next_command) {
    Command cmd;
    cmd.command_type = command_type;
    cmd.p0 = p0;
    cmd.p1 = p1;
    cmd.next_command = next_command;
    return cmd;
}

/**
 *
 */
void generate_print(LLVMValueRef value) {
    LLVMValueRef printf_func = LLVMGetNamedFunction(module, "printf");
    LLVMTypeRef printf_args[] = {LLVMPointerType(LLVMInt8Type(), 0)};
    LLVMTypeRef printf_func_ref = LLVMFunctionType(LLVMInt32Type(), printf_args, 1, 1);
    if (!printf_func) {
        printf_func = LLVMAddFunction(module, "printf", printf_func_ref);
    }
    LLVMValueRef format_str = LLVMBuildGlobalStringPtr(builder, "%d\n", EMPTY_NAME);
    LLVMValueRef args[] = {format_str, value};
    LLVMBuildCall2(builder, printf_func_ref, printf_func, args, 2, EMPTY_NAME);
}
