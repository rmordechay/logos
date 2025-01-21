#ifndef LOGOSUTILS_H
#define LOGOSUTILS_H

#include "LogosDefinitions.h"
#include <__filesystem/directory_entry.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/Target/TargetMachine.h>

using namespace std;
using namespace llvm;

class Utils {
public:
    static bool isLogosFile(const filesystem::directory_entry& filePath);
    static bool isMainFile(const filesystem::directory_entry& filePath);
    static Module* createLLVMModuleFromFile(const string& filePath, LLVMContext& context, const TargetMachine& tm);
    static void emitLLVMFile(const string& filePath, const Module* module);
};

#endif //LOGOSUTILS_H
