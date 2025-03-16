#ifndef CODEGENERATION_H
#define CODEGENERATION_H

#include <Token.h>
#include <llvm/IR/Value.h>
#include "LgsGlobals.h"

class LgsValue {
public:
    Location location;

    void setIRValue(Value* value);
    Value* getIRValue(CodeGenMetadata* metadata);
    virtual void setPosition(const antlr4::Token* ctx);
    static BasicBlock* createBasicBlock(const char* name);
    static void startBlock(CodeGenMetadata* metadata, BasicBlock* block);
    virtual json asJson();
    virtual ~LgsValue() = default;
private:
    virtual Value* createIRValue(CodeGenMetadata* metadata) = 0;
    Value* IRValue = nullptr;
};

inline void LgsValue::setPosition(const antlr4::Token* ctx) {
    location.lineNumber = ctx->getLine();
    location.posInLine = ctx->getCharPositionInLine() + 1;
}

inline Value* LgsValue::getIRValue(CodeGenMetadata* metadata) {
    if (!IRValue) {
        IRValue = createIRValue(metadata);
    }
    return IRValue;
}

inline void LgsValue::startBlock(CodeGenMetadata* metadata, BasicBlock* const block) {
    const auto currentFunc = metadata->logosStack.currentFunc;
    auto& builder = metadata->builder;
    block->insertInto(currentFunc);
    builder.SetInsertPoint(block);
}

inline BasicBlock* LgsValue::createBasicBlock(const char* name) {
    return BasicBlock::Create(context, name);
}

inline json LgsValue::asJson() {
    return json::object();
}

inline void LgsValue::setIRValue(Value* value) {
    IRValue = value;
}

#endif //CODEGENERATION_H
