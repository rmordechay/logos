#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include "CodeNode.h"
#include "exprs/LogosExpr.h"

#include <map>
#include <llvm/IR/IRBuilder.h>

using namespace llvm;

class CodeGenerator {
public:
    void run(const std::vector<CodeNode*>& codeNodes);
    void declareFunctions(Module* module);
    void insertMain(Module* module);
    void addStoreExpr(const std::string& name, LogosExpr* expr);

    void writeToFile(const Module* module);
    void runBinary();
    void compileLLVM(const std::string& llvmFilePath, const std::string& outputFilePath);
    ~CodeGenerator() = default;

private:
    LLVMContext context;
    IRBuilder<> builder = IRBuilder(context);
    std::vector<CodeNode*> codeNodes;
    std::map<std::string, Function*> functions;
};

#endif //CODEGENERATOR_H
