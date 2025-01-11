#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include <llvm/IR/IRBuilder.h>

using namespace llvm;

class CodeGenerator {
public:
    void run();
    void insertMain(LLVMContext& context, IRBuilder<>& builder, Module* module);
    void writeToFile(const Module* module);
    void runBinary();
    void compileLLVM(const std::string& llvmFilePath, const std::string& outputFilePath);
private:
    LLVMContext context;
    IRBuilder<> builder = IRBuilder(context);
    IntegerType* int32Ty = builder.getInt32Ty();
};

#endif //CODEGENERATOR_H
