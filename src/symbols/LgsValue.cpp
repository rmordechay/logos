#include "LgsValue.h"

#include "funcs/LgsFunc.h"
#include "types/LgsFuncType.h"

#include "json/json.hpp"

#include <TokenSource.h>

void LgsValue::setLocation(const antlr4::Token* ctx) {
    location.lineNumber = ctx->getLine();
    location.posInLine = ctx->getCharPositionInLine() + 1;
}

void LgsValue::startBlock(CodeGenMetadata* metadata, BasicBlock* const block) const {
    block->insertInto(metadata->lgsStack.currentFunc->createIRFunc(metadata));
    metadata->builder.SetInsertPoint(block);
}

Value* LgsValue::createIRStr(Module* module, const std::string& value) const {
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

void LgsValue::setIRValue(Value* value) {
    IRValue = value;
}