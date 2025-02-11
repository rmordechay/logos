#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H
#include "CodeGeneration.h"
#include "LogosStack.h"
#include "files/LogosMainFile.h"

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


    void generateMainModule(const LogosMainFile* mainFile, CodeGenMetadata metadata);
    void run(const map<string, LogosFile*>& files, LogosStack& theStack);
    Linker* linkModules(Module* rootModule) const;
    void initLLVM();
    static void runBinary();
    static void generateTest();
    void emitLLVMFile(const string& filePath, const Module* module);
    ~CodeGenerator();

};

#endif //CODEGENERATOR_H
