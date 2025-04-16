#include "LgsValue.h"

#include "funcs/LgsFunc.h"

#include <TokenSource.h>

void LgsValue::setLocation(const antlr4::Token* ctx) {
    location.lineNumber = ctx->getLine();
    location.posInLine = ctx->getCharPositionInLine() + 1;
}

void LgsValue::startBlock(CodeGenMetadata* metadata, BasicBlock* const block) const {
    block->insertInto(metadata->lgsStack.currentFunc->getIRFunc(metadata));
    metadata->builder.SetInsertPoint(block);
}

Value* LgsValue::createIRStr(Module* module, const std::string& value) const {
    const auto strConstant = ConstantDataArray::getString(context, value, true);
    return createIRGlobal(module, strConstant);
}

string LgsValue::format(string& indentStr) {
    assert(false);
}

BasicBlock* LgsValue::createBasicBlock(const char* name) const {
    return BasicBlock::Create(context, name);
}

void LgsValue::free(CodeGenMetadata* metadata) {
    assert(false && "value has nothing to free");
}

Value* LgsValue::hashIRValue(CodeGenMetadata* metadata, Value* value) const {
    const auto hashValueIRFuncType = FunctionType::get(i32Ty, {ptrTy}, false);
    const auto func = metadata->module->getOrInsertFunction("hash_Str", hashValueIRFuncType);
    return metadata->builder.CreateCall(func, {value});
}

void LgsValue::setIRValue(Value* value) {
    IRValue = value;
}

GlobalVariable* LgsValue::createIRGlobal(Module* module, Constant* strConstant) const {
    return new GlobalVariable(*module, strConstant->getType(), true, GlobalValue::PrivateLinkage, strConstant);
}