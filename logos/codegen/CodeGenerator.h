#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H
#include "CodeNode.h"
#include "exprs/LogosExpr.h"
#include <map>
#include <stack>
#include <llvm/IR/IRBuilder.h>

using namespace llvm;
using namespace std;

class CodeGenerator {
public:
    void generate(const vector<CodeNode*>& codeNodes, RuntimeStackFrame rootFrame, Module* module);
    void run(const vector<CodeNode*>& codeNodes);
    void declareFunctions(Module* module, RuntimeStackFrame* rootFrame);
    void insertFunction(Module* module, const string& name, IntegerType* rt, RuntimeStackFrame* frame);
    void runBinary();
    void compileLLVM(const string& llvmFilePath, const string& outputFilePath);
    auto linkModules(const std::vector<std::unique_ptr<Module>>& modules, LLVMContext& context) -> Error;
    ~CodeGenerator() = default;

private:
    LLVMContext context;
    IRBuilder<> builder = IRBuilder(context);
    vector<CodeNode*> codeNodes;
};

#endif //CODEGENERATOR_H
