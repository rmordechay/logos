#ifndef LOGOSMETADATA_H
#define LOGOSMETADATA_H

#include "LogosStack.h"

#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>

using namespace llvm;

inline LLVMContext context;

struct CodeGenMetadata {
    IRBuilder<>* builder;
    LogosStack* theStack;
    Module* module;
};

struct Position {
    size_t lineNumber;
    size_t posInLine;
    const string* filePath = nullptr;
};

#endif //LOGOSMETADATA_H
