#ifndef CODEGENERATION_H
#define CODEGENERATION_H

#include "CodeGenerator.h"

#include <llvm/IR/IRBuilder.h>
#include <Token.h>

using namespace llvm;
using namespace std;

class LogosValue {
public:
    Position position = Position();
    Value* getLLVMValue(CodeGenMetadata* metadata);
    virtual void setPosition(const antlr4::Token* ctx, const string& filePath);
    virtual ~LogosValue() = default;
protected:
    virtual Value *computeLLVMValue(CodeGenMetadata* metadata) = 0;
private:
    Value* llvmValue = nullptr;
};

inline void LogosValue::setPosition(const antlr4::Token* ctx, const string& filePath) {
    position.lineNumber = ctx->getLine();
    position.posInLine = ctx->getCharPositionInLine();
    position.filePath = &filePath;
}

inline Value* LogosValue::getLLVMValue(CodeGenMetadata* metadata) {
    if (!llvmValue) {
        llvmValue = computeLLVMValue(metadata);
    }
    return llvmValue;
}

#endif //CODEGENERATION_H
