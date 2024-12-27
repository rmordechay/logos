#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H
#include "CodeNode.h"

#include <llvm/IR/IRBuilder.h>

using namespace llvm;

class CodeGenerator {
public:
    static void generateCode(const std::vector<CodeNode*>& codeNodes);
    static void insertMain(LLVMContext& context, IRBuilder<>& builder, Module* module);
    static void writeToFile(const Module* module);
    static void runBinary();
};

#endif //CODEGENERATOR_H
