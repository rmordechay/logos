#include "LgsValue.h"

#include "funcs/LgsFunc.h"

void LgsValue::setLocation(const antlr4::Token* ctx) {
    location.lineNumber = ctx->getLine();
    location.posInLine = ctx->getCharPositionInLine() + 1;
}

void LgsValue::startBlock(CodeGenMetadata* metadata, BasicBlock* const block) const {
    block->insertInto(metadata->logosStack.currentFunc->IRFunc);
    metadata->builder.SetInsertPoint(block);
}

BasicBlock* LgsValue::createBasicBlock(const char* name) const {
    return BasicBlock::Create(context, name);
}

json LgsValue::asJson() {
    return json::object();
}

void LgsValue::free(CodeGenMetadata* metadata) {
    assert(false && "value has nothing to free");
}

void LgsValue::setIRValue(Value* value) {
    IRValue = value;
}

GlobalVariable* LgsValue::createIRGlobal(Module* module, Constant* strConstant) const {
    return new GlobalVariable(*module, strConstant->getType(), true, GlobalValue::PrivateLinkage, strConstant);
}