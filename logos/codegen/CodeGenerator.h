#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H
#include "LogosStack.h"

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
    void run(const vector<LogosFile*>& files);
    Linker* linkModules(Module* rootModule) const;
    void initLLVM();
    static void runBinary();
    static void generateTest();
    void emitLLVMFile(const string& filePath, const Module* module);
    ~CodeGenerator();

};

#endif //CODEGENERATOR_H
