#include "LgsValue.h"
#include "funcs/LgsFunc.h"
#include "json/json.hpp"

void LgsValue::startBlock(CodeGenMetadata* metadata, BasicBlock* const block) const {
    const auto IRFunc = metadata->runtime.getCurrentFunc()->getIRFunc(metadata);
    block->insertInto(IRFunc);
    metadata->builder.SetInsertPoint(block);
}

void LgsValue::startBlockFunc(CodeGenMetadata* metadata) const {
    const auto currentFunc = metadata->runtime.getCurrentFunc();
    currentFunc->entryBlock->insertInto(currentFunc->getIRFunc(metadata));
    metadata->builder.SetInsertPoint(currentFunc->entryBlock);
}

Value* LgsValue::getIRStr(Module* module, const string& value) const {
    for (auto& globals : module->globals()) {
        if (!globals.hasInitializer()) continue;
        const auto dataArray = dyn_cast<ConstantDataArray>(globals.getInitializer());
        if (!dataArray || !dataArray->isCString() || dataArray->getAsCString() != value) continue;
        return &globals;
    }
    const auto strConstant = ConstantDataArray::getString(context, value, true);
    return new GlobalVariable(*module, strConstant->getType(), true, GlobalValue::PrivateLinkage, strConstant);
}

string LgsValue::format(string& indentStr) {
    assert(false);
}

BasicBlock* LgsValue::createBasicBlock(const char* name) const {
    return BasicBlock::Create(context, name);
}

Value* LgsValue::hashIRValue(CodeGenMetadata* metadata, Value* value) const {
    const auto hashValueIRFuncType = FunctionType::get(i32Ty, {ptrTy}, false);
    const auto func = metadata->module->getOrInsertFunction("hash_Str", hashValueIRFuncType);
    return metadata->builder.CreateCall(func, {value});
}

json LgsValue::asJSON() {
    assert(false);
}

void LgsValue::setLocation(const antlr4::Token* ctx) {
    location.lineNumber = ctx->getLine();
    location.posInLine = ctx->getCharPositionInLine() + 1;
}

void LgsValue::setIRValue(Value* value) {
    IRValue = value;
}