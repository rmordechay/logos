#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H
#include "../sema/ASTNode.h"

#include <llvm/IR/LLVMContext.h>

using namespace llvm;

class CodeGenerator {
public:
    LLVMContext context = LLVMContext();

    void generateCodeDemo();
    void generateCode(const std::vector<ASTNode>& vector);
    static void writeToFile(const Module* module);
    static void runBinary();
};

#endif //CODEGENERATOR_H
