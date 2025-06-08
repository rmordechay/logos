#include "LgsValue.h"
#include "funcs/LgsFunc.h"
#include "json/json.hpp"

void LgsValue::startBlock(LgsRuntime* runtime, BasicBlock* const block) const {
    block->insertInto(runtime->stack.currentFunc->getIRFunc(runtime));
    runtime->builder.SetInsertPoint(block);
}

void LgsValue::startBlockFunc(LgsRuntime* runtime) const {
    const auto currentFunc = runtime->stack.currentFunc;
    const auto IRFunc = currentFunc->getIRFunc(runtime);
    const auto entryBlock = BasicBlock::Create(runtime->module->getContext(), "entry", IRFunc);
    runtime->builder.SetInsertPoint(entryBlock);
}

BasicBlock* LgsValue::createBasicBlock(const char* name, LLVMContext& context) const {
    return BasicBlock::Create(context, name);
}

Value* LgsValue::hashIRValue(LgsRuntime* runtime, Value* value) const {
    const auto hashValueIRFuncType = FunctionType::get(runtime->builder.getInt32Ty(), {PointerType::getUnqual(context)}, false);
    const auto func =runtime->module->getOrInsertFunction("hash_Str", hashValueIRFuncType);
    return runtime->builder.CreateCall(func, {value});
}

void LgsValue::setLocation(const antlr4::Token* ctx) {
    location.lineNumber = ctx->getLine();
    location.posInLine = ctx->getCharPositionInLine() + 1;
}

void LgsValue::setIRValue(Value* value) {
    IRValue = value;
}

string LgsValue::format(string& indentStr) {
    assert(false);
}

json LgsValue::asJSON() {
    assert(false);
}
