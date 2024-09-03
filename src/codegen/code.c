#include <llvm-c/Core.h>
#include <stddef.h>

/**
 * Generates the IR code for a printf call.
 */
void generate_print_code(LLVMBuilderRef builder, LLVMModuleRef module) {
    LLVMValueRef str = LLVMBuildGlobalStringPtr(builder, "Hello\n", "str");

    LLVMValueRef printf_func = LLVMGetNamedFunction(module, "printf");
    LLVMTypeRef printf_args[] = {LLVMPointerType(LLVMInt8Type(), 0)};
    LLVMTypeRef printf_func_type = LLVMFunctionType(LLVMInt32Type(), printf_args, 1, 1);
    if (!printf_func) {
        printf_func = LLVMAddFunction(module, "printf", printf_func_type);
    }
    LLVMValueRef args[] = {str};
    LLVMBuildCall2(builder, printf_func_type, printf_func, args, 1, "call_printf");
}

/**
*
*/
void llvm() {
    LLVMModuleRef module = LLVMModuleCreateWithName("module");
    LLVMBuilderRef builder = LLVMCreateBuilder();

    LLVMTypeRef main_func_type = LLVMFunctionType(LLVMInt32Type(), NULL, 0, 0);
    LLVMValueRef main_func = LLVMAddFunction(module, "main", main_func_type);
    LLVMBasicBlockRef entry_block = LLVMAppendBasicBlock(main_func, "entry_block");
    LLVMPositionBuilderAtEnd(builder, entry_block);
    generate_print_code(builder, module);

    LLVMBuildRet(builder, LLVMConstInt(LLVMInt32Type(), 0, 0));
    LLVMDumpModule(module);
    LLVMPrintModuleToFile(module, "output.ll", NULL);

    LLVMDisposeBuilder(builder);
    LLVMDisposeModule(module);
}