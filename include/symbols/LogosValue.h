#ifndef CODEGENERATION_H
#define CODEGENERATION_H

#include <Token.h>
#include <llvm/IR/Value.h>
#include "codegen/LogosMetadata.h"

constexpr auto privateLinkage = GlobalValue::PrivateLinkage;

class LogosValue {
public:
    Position position = Position();

    void setIRValue(Value* value);
    Value* getIRValue(CodeGenMetadata* metadata);
    virtual void setPosition(const antlr4::Token* ctx);
    virtual Value* createIRValue(CodeGenMetadata* metadata) = 0;
    static BasicBlock* createBasicBlock(const char* name);
    static void startBlock(CodeGenMetadata* metadata, BasicBlock* block);
    virtual ~LogosValue() = default;
private:
    Value* IRValue = nullptr;
};

inline void LogosValue::setPosition(const antlr4::Token* ctx) {
    position.lineNumber = ctx->getLine();
    position.posInLine = ctx->getCharPositionInLine() + 1;
}

inline Value* LogosValue::getIRValue(CodeGenMetadata* metadata) {
    if (!IRValue) {
        IRValue = createIRValue(metadata);
    }
    return IRValue;
}

inline void LogosValue::startBlock(CodeGenMetadata* metadata, BasicBlock* const block) {
    const auto currentFunc = metadata->logosStack.currentFunc;
    auto& builder = metadata->builder;
    block->insertInto(currentFunc);
    builder.SetInsertPoint(block);
}

inline BasicBlock* LogosValue::createBasicBlock(const char* name) {
    return BasicBlock::Create(context, name);
}

inline void LogosValue::setIRValue(Value* value) {
    IRValue = value;
}

#endif //CODEGENERATION_H
