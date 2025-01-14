#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include "CodeNode.h"
#include "exprs/LogosExpr.h"

#include <map>
#include <llvm/IR/IRBuilder.h>

using namespace llvm;
using namespace std;

class CodeGenerator {
public:
    void run(const vector<CodeNode*>& codeNodes);
    void declareFunctions(Module* module, RuntimeScope* scope);
    void insertFunction(Module* module, const string& name, Type* rt, RuntimeScope* scope);
    void runBinary(const Module& module);
    void compileLLVM(const string& llvmFilePath, const string& outputFilePath);
    ~CodeGenerator() = default;

private:
    LLVMContext context;
    IRBuilder<> builder = IRBuilder(context);
    vector<CodeNode*> codeNodes;
};

#endif //CODEGENERATOR_H
