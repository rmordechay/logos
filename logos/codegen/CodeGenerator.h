#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include "LogosCodeNode.h"

#include <llvm/IR/IRBuilder.h>

using namespace llvm;

class CodeGenerator {
public:
    static void generateCode(const std::vector<std::shared_ptr<LogosCodeNode>>& codeNodes);
    static void insertMain(LLVMContext& context, IRBuilder<>& builder, Module* module);
    static void writeToFile(const Module* module);
    static void runBinary();
    static void compileLLVM(const std::string& llvmFilePath, const std::string& outputFilePath);
};

#endif //CODEGENERATOR_H
