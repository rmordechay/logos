#ifndef LOGOSUTILS_H
#define LOGOSUTILS_H

#include "LogosDefinitions.h"
#include "exprs/LogosInstance.h"
#include "funcs/LogosFunc.h"

#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Target/TargetMachine.h>
#include "llvm/Support/FileSystem.h"
#include <__filesystem/directory_entry.h>
#include <exprs/LogosVariable.h>

using namespace std;
using namespace llvm;

class Utils {
public:
    static bool isLogosFile(const filesystem::directory_entry& filePath);
    static bool isMainFile(const filesystem::directory_entry& filePath);
    static LogosSymbol createSymbol(LogosExpr* expr);
    static Module* createIRModuleFromFile(const string& filePath, LLVMContext& context, const TargetMachine& tm);
    static void emitIRFile(const string& filePath, const Module* module);
};


#endif //LOGOSUTILS_H
