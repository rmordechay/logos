#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H
#include "CodeGeneration.h"
#include "LogosStack.h"
#include "files/LogosMainFile.h"
#include "files/LogosObjectFile.h"

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

    CodeGenerator() { initLLVM(); }
    void generateMainModule(const LogosMainFile* mainFile, CodeGenMetadata metadata);
    void run(const map<string, LogosFile*>& files, LogosStack& theStack);
    void initLLVM();
    static void runBinary();
    static void generateTest();
    static void generateObjModule(const LogosObject* obj, IRBuilder<>* builder, const LogosStack* theStack);
    void emitLLVMFile(const string& filePath, const Module* module);
    ~CodeGenerator() = default;
};

#endif //CODEGENERATOR_H
