#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H
#include "LogosPackage.h"
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
    void run(const LogosPackage* rootPackage);
    void generatePackage(const LogosPackage* package, vector<Module*>& modules, IRBuilder<>& builder);
    Linker* linkModules(const vector<Module*>& modules, LLVMContext& context) const;
    void initLLVM();
    static void runBinary();
    static void generateTest();
    ~CodeGenerator() = default;

private:
    vector<CodeGeneration*> codeNodes;
    TargetMachine* targetMachine = nullptr;
};

#endif //CODEGENERATOR_H
