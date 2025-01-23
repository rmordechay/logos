#ifndef CODEGENERATION_H
#define CODEGENERATION_H
#include "LogosStack.h"
#include "types/LogosType.h"

#include <Token.h>
#include <llvm/IR/IRBuilder.h>

namespace antlr4 {
    class Token;
}

using namespace llvm;
using namespace std;

struct Position {
    int lineNumber;
    int posInLine;
    const string* filePath = nullptr;
};

class CodeGeneration {
public:
    Position position = Position();
    virtual Value* getLLVMValue(IRBuilder<>* builder, LogosStack* stack, Module* module) = 0;
    virtual void setPosition(const antlr4::Token* ctx, const string& filePath);
    virtual ~CodeGeneration() = default;
};

inline void CodeGeneration::setPosition(const antlr4::Token* ctx, const string& filePath) {
    position.lineNumber = ctx->getLine();
    position.posInLine = ctx->getCharPositionInLine();
    position.filePath = &filePath;
}

#endif //CODEGENERATION_H
