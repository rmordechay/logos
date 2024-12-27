#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H
#include "CodeNode.h"

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>

using namespace llvm;

class CodeGenerator {
public:
    LLVMContext context = LLVMContext();

    void generateCodeDemo();
    void insertMain(IRBuilder<>& builder, Module* module);
    void generateCode(const std::vector<CodeNode*>& codeNodes);
    static void writeToFile(const Module* module);
    static void runBinary();
};

#endif //CODEGENERATOR_H
