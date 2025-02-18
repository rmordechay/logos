#ifndef LOGOSMETADATA_H
#define LOGOSMETADATA_H

#include <llvm/IR/IRBuilder.h>

class CodeGenerator;
class LogosStack;
using namespace llvm;

inline LLVMContext context;

struct CodeGenMetadata {
    IRBuilder<>* builder;
    LogosStack* theStack;
    Module* module;
    CodeGenerator* codeGen;
};

struct Position {
    size_t lineNumber;
    size_t posInLine;
    const std::string* filePath = nullptr;
};

#endif //LOGOSMETADATA_H
