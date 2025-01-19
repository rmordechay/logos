#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H
#include "LogosRootPackage.h"
#include "exprs/LogosExpr.h"
#include "files/LogosMainFile.h"

#include <map>
#include <llvm/IR/IRBuilder.h>
#include <llvm/MC/TargetRegistry.h>

using namespace llvm;
using namespace std;

class CodeGenerator {
public:
    void run(const LogosRootPackage* rootPackage);
    Module* generateMainModule(const LogosMainFile* mainFile);
    void declareFunctions(Module* module, stack<LogosStackFrame>* rootFrame);
    void runBinary();
    void initLLVM();
    unique_ptr<Module> compileLLVMFile(const string& inputFile);
    void linkModules(unique_ptr<Module> module);
    void generateTest();
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
