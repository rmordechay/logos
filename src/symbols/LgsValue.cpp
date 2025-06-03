#include "LgsValue.h"
#include "funcs/LgsFunc.h"
#include "json/json.hpp"

void LgsValue::startBlock(BasicBlock* const block, Function* IRFunc) const {
    block->insertInto(IRFunc);
    builder.SetInsertPoint(block);
}

void LgsValue::startBlockFunc(Module* module, LgsFunc* currentFunc) const {
    const auto entryBlock = BasicBlock::Create(context, "entry");
    entryBlock->insertInto(currentFunc->getIRFunc(module));
    builder.SetInsertPoint(entryBlock);
}

string LgsValue::format(string& indentStr) {
    assert(false);
}

BasicBlock* LgsValue::createBasicBlock(const char* name) const {
    return BasicBlock::Create(context, name);
}

Value* LgsValue::hashIRValue(Module* module, Value* value) const {
    const auto hashValueIRFuncType = FunctionType::get(i32Ty, {ptrTy}, false);
    const auto func = module->getOrInsertFunction("hash_Str", hashValueIRFuncType);
    return builder.CreateCall(func, {value});
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