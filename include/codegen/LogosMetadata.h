#ifndef LOGOSMETADATA_H
#define LOGOSMETADATA_H

#include <LogosStack.h>
#include <llvm/IR/IRBuilder.h>
#include <map>

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
};

struct Position {
    size_t lineNumber;
    size_t posInLine;
    const string* filePath = nullptr;
};

#endif //LOGOSMETADATA_H
