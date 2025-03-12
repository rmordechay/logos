#ifndef LOGOSMETADATA_H
#define LOGOSMETADATA_H

#include <LogosStack.h>
#include <llvm/IR/IRBuilder.h>
#include <filesystem>

class CodeGenerator;
class LogosStack;

using namespace llvm;
using namespace std;

inline LLVMContext context;
inline map<string, Module*> modules;

struct CodeGenMetadata {
    LogosStack logosStack;
    Module* currentModule;
    IRBuilder<> builder = IRBuilder(context);
    filesystem::path buildDir;
};

struct Position {
    size_t lineNumber{};
    size_t posInLine{};
};

inline bool moduleExists(const string& name) {
    return modules.find(name) != modules.end();
}

#endif //LOGOSMETADATA_H
