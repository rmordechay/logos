#include "LgsValue.h"
#include "codegen/CodegenMetadata.h"
#include "funcs/LgsFunc.h"
#include "logos/LgsRuntime.h"
#include "json/json.hpp"

void LgsValue::startBlock(LgsRuntime* runtime, BasicBlock* const block, Function* IRFunc) const {
    block->insertInto(IRFunc);
    runtime->builder.SetInsertPoint(block);
}

void LgsValue::startBlockFunc(LgsRuntime* runtime) const {
    const auto entryBlock = BasicBlock::Create(context, "entry");
    const auto IRFunc = runtime->stack.currentFunc->getIRFunc(runtime);
    entryBlock->insertInto(IRFunc);
    runtime->builder.SetInsertPoint(entryBlock);
}

string LgsValue::format(string& indentStr) {
    assert(false);
}

BasicBlock* LgsValue::createBasicBlock(const char* name) const {
    return BasicBlock::Create(context, name);
}

Value* LgsValue::hashIRValue(LgsRuntime* runtime, Value* value) const {
    const auto hashValueIRFuncType = FunctionType::get(i32Ty, {ptrTy}, false);
    const auto func =runtime->module->getOrInsertFunction("hash_Str", hashValueIRFuncType);
    return runtime->builder.CreateCall(func, {value});
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