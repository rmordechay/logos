#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H
#include "application/LogosPackage.h"
#include "exprs/LogosExpr.h"
#include "files/LogosMainFile.h"
#include "files/LogosObjectFile.h"

#include <map>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Linker/Linker.h>
#include <llvm/MC/TargetRegistry.h>

using namespace llvm;
using namespace std;

class CodeGenerator {
public:
    LLVMContext context;
    vector<Module*> modules;
    vector<CodeGeneration*> codeNodes;
    IRBuilder<> builder = IRBuilder(context);

    TargetMachine* targetMachine = nullptr;

    explicit CodeGenerator() {
        initLLVM();
    }

    void run(const map<string, LogosFile*>& files);
    Linker* linkModules() const;
    void initLLVM();
    static void runBinary();
    static void generateTest();
    ~CodeGenerator();

};

#endif //CODEGENERATOR_H
