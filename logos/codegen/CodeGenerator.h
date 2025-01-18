#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H
#include "exprs/LogosExpr.h"
#include <map>
#include <stack>
#include <llvm/IR/IRBuilder.h>
#include <llvm/MC/TargetRegistry.h>

using namespace llvm;
using namespace std;

class CodeGenerator {
public:
    void run(const vector<CodeGeneration*>& codeNodes);
    void declareFunctions(Module* module, RuntimeStackFrame* rootFrame);
    void insertFunction(Module* module, const string& name, IntegerType* rt, RuntimeStackFrame* frame);
    void runBinary();
    static void initLLVM();
    void initTargetMachine();
    unique_ptr<Module> compileModule(const string& inputFile);
    void linkModules();
    ~CodeGenerator() = default;

private:
    LLVMContext context;
    IRBuilder<> builder = IRBuilder(context);
    vector<CodeGeneration*> codeNodes;
    std::string targetTriple;
    const Target* target = nullptr;
    TargetMachine* targetMachine = nullptr;
};

#endif //CODEGENERATOR_H
