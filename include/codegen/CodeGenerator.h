#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H
#include "LogosStack.h"
#include "CodeGeneration.h"
#include "files/LogosMainFile.h"
#include "files/LogosObjectFile.h"

#include <llvm/IR/Module.h>
#include <llvm/Support/TargetSelect.h>
#include "llvm/Passes/PassBuilder.h"
#include <clang/Frontend/CompilerInstance.h>

class ThreadPool;
using namespace llvm;
using namespace std;

namespace llvm {
    class Linker;
    class TargetMachine;
}
class LogosFile;
class CodeGeneration;

inline LLVMContext context;

class CodeGenerator {
public:
    vector<Module*> modules;
    vector<CodeGeneration*> codeNodes;

    CodeGenerator() { initLLVM(); }
    static void run(const map<string, LogosFile*>& files, LogosStack& theStack);
    static void initLLVM();
    static void runBinary();
    static void generateTest();
    static void generateMainModule(const LogosMainFile* mainFile, CodeGenMetadata metadata, IRBuilder<>& builder);
    static void generateObjModule(LogosObject* obj, const LogosStack* theStack);
    static void emitLLVMFile(const string& filePath, const Module* module);
    ~CodeGenerator() = default;
};

#endif //CODEGENERATOR_H
