#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H
#include "LogosPackage.h"
#include "exprs/LogosExpr.h"
#include "files/LogosMainFile.h"
#include "files/LogosObjectFile.h"

#include <map>
#include <llvm/IR/IRBuilder.h>
#include <llvm/MC/TargetRegistry.h>

using namespace llvm;
using namespace std;

class CodeGenerator {
public:
    void run(const LogosPackage* rootPackage);
    Module* createEmptyModule(const string& name, const IRBuilder<>* builder) const;
    Module* generateMainModule(const LogosMainFile* mainFile);
    Module* generateObjModule(const LogosObjectFile* file) const;
    void declareFunctions(Module* module, stack<LogosStackFrame>* rootFrame, IRBuilder<>* builder);
    void runBinary();
    void initLLVM();
    unique_ptr<Module> compileLLVMFile(const string& inputFile, LLVMContext* context);
    void linkModules(unique_ptr<Module> module);
    static void emitLLVMFile(const string& filePath, const Module* module);
    static void generateTest();
    ~CodeGenerator() = default;

private:
    vector<CodeGeneration*> codeNodes;
    std::string targetTriple;
    const Target* target = nullptr;
    TargetMachine* targetMachine = nullptr;
};

#endif //CODEGENERATOR_H
