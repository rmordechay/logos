#ifndef CODEGENERATION_H
#define CODEGENERATION_H

#include "LogosStack.h"

#include <llvm/IR/IRBuilder.h>
#include <Token.h>

namespace antlr4 {
    class Token;
}

using namespace llvm;
using namespace std;


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

class CodeGeneration {
public:
    Position position = Position();
    virtual Value *getLLVMValue(CodeGenMetadata* metadata) = 0;
    virtual void setPosition(const antlr4::Token* ctx, const string& filePath);
    virtual ~CodeGeneration() = default;
};

inline void CodeGeneration::setPosition(const antlr4::Token* ctx, const string& filePath) {
    position.lineNumber = ctx->getLine();
    position.posInLine = ctx->getCharPositionInLine();
    position.filePath = &filePath;
}

#endif //CODEGENERATION_H
