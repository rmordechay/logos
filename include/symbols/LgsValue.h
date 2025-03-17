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
    GlobalVariable* createIRGlobal(Module* module, Constant* strConstant) const;
    virtual void setLocation(const antlr4::Token* ctx);
    virtual json asJson();
    static BasicBlock* createBasicBlock(const char* name);
    static void startBlock(CodeGenMetadata* metadata, BasicBlock* block);
    virtual ~LgsValue() = default;
private:
    virtual Value* createIRValue(CodeGenMetadata* metadata) = 0;
    Value* IRValue = nullptr;
};

inline void LgsValue::setLocation(const antlr4::Token* ctx) {
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

inline GlobalVariable* LgsValue::createIRGlobal(Module* module, Constant* strConstant) const {
    return new GlobalVariable(*module, strConstant->getType(), true, GlobalValue::PrivateLinkage, strConstant);
}

#endif //CODEGENERATION_H
