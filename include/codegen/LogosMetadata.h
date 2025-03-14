#ifndef LOGOSMETADATA_H
#define LOGOSMETADATA_H

#include <LgsStack.h>
#include <llvm/IR/IRBuilder.h>
#include <filesystem>

class CodeGenerator;
class LgsStack;

using namespace llvm;
using namespace std;

inline LLVMContext context;
inline map<string, Module*> modules;

struct CodeGenMetadata {
    LgsStack logosStack;
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
