#include "LgsValue.h"

void LgsValue::setLocation(const antlr4::Token* ctx) {
    location.lineNumber = ctx->getLine();
    location.posInLine = ctx->getCharPositionInLine() + 1;
}

Value* LgsValue::getIRValue(CodeGenMetadata* metadata) {
    if (!IRValue) {
        IRValue = createIRValue(metadata);
    }
    return IRValue;
}

void LgsValue::startBlock(CodeGenMetadata* metadata, BasicBlock* const block, const bool enterScope) {
    if (enterScope) metadata->logosStack.enterScope();
    const auto currentFunc = metadata->logosStack.currentFunc;
    auto& builder = metadata->builder;
    block->insertInto(currentFunc);
    builder.SetInsertPoint(block);
}

BasicBlock* LgsValue::createBasicBlock(const char* name) {
    return BasicBlock::Create(context, name);
}

json LgsValue::asJson() {
    return json::object();
}

void LgsValue::setIRValue(Value* value) {
    IRValue = value;
}

GlobalVariable* LgsValue::createIRGlobal(Module* module, Constant* strConstant) const {
    return new GlobalVariable(*module, strConstant->getType(), true, GlobalValue::PrivateLinkage, strConstant);
}