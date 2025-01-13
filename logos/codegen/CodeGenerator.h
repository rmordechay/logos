#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include "exprs/LogosExpr.h"

#include <map>
#include <llvm/IR/IRBuilder.h>

using namespace llvm;
using namespace std;

class CodeGenerator {
public:
    void run();
    void declareFunctions(Module* module);
    void insertMain(Module* module);

    void writeToFile(const Module* module);
    void runBinary();
    void compileLLVM(const string& llvmFilePath, const string& outputFilePath);
    ~CodeGenerator() = default;

private:
    LLVMContext context;
    IRBuilder<> builder = IRBuilder(context);
    map<string, Function*> functions;
};

#endif //CODEGENERATOR_H
