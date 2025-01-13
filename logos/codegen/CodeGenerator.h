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
    void declareFunctions(Module* module);
    void insertMain(Module* module);
    void addStoreExpr(const string& name, LogosExpr* expr);

    void writeToFile(const Module* module);
    void runBinary();
    void compileLLVM(const string& llvmFilePath, const string& outputFilePath);
    ~CodeGenerator() = default;

private:
    LLVMContext context;
    IRBuilder<> builder = IRBuilder(context);
    vector<CodeNode*> codeNodes;
    map<string, Function*> functions;
};

#endif //CODEGENERATOR_H
