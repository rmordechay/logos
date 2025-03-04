#ifndef CODEGENERATION_H
#define CODEGENERATION_H


#include <Token.h>
#include <llvm/IR/Value.h>
#include "codegen/LogosMetadata.h"

class LogosValue {
public:
    Position position = Position();
    Value* writeIRValue(CodeGenMetadata* metadata);
    void setIRValue(Value* value);
    virtual void setPosition(const antlr4::Token* ctx, const string& filePath);
    virtual ~LogosValue() = default;

protected:
    virtual Value* computeIRValue(CodeGenMetadata* metadata) = 0;
    static void startBlock(CodeGenMetadata* metadata, BasicBlock* block);
private:
    Value* IRValue = nullptr;
};

inline void LogosValue::setPosition(const antlr4::Token* ctx, const string& filePath) {
    position.lineNumber = ctx->getLine();
    position.posInLine = ctx->getCharPositionInLine();
    position.filePath = &filePath;
}

inline Value* LogosValue::writeIRValue(CodeGenMetadata* metadata) {
    if (!IRValue) {
        IRValue = computeIRValue(metadata);
    }
    return IRValue;
}

inline void LogosValue::startBlock(CodeGenMetadata* metadata, BasicBlock* const block) {
    const auto currentFunc = metadata->logosStack.currentFunc;
    auto& builder = metadata->builder;
    block->insertInto(currentFunc);
    builder.SetInsertPoint(block);
}

inline void LogosValue::setIRValue(Value* value) {
    IRValue = value;
}

#endif //CODEGENERATION_H
