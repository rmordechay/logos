#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H
#include "LogosStack.h"
#include "application/ThreadPool.h"

#include <map>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>

class ThreadPool;
using namespace llvm;
using namespace std;

namespace llvm {
    class Linker;
    class TargetMachine;
}
class LogosFile;
class CodeGeneration;

class CodeGenerator {
public:
    LLVMContext context;
    vector<Module*> modules;
    vector<CodeGeneration*> codeNodes;
    IRBuilder<> builder = IRBuilder(context);
    TargetMachine* targetMachine = nullptr;


    void declareBuiltinFuncs(LogosStack& theStack, Module* rootModule);
    void run(const map<string, LogosFile*>& files);
    Linker* linkModules(Module* rootModule) const;
    void initLLVM();
    static void runBinary();
    static void generateTest();
    ~CodeGenerator();

};

#endif //CODEGENERATOR_H
