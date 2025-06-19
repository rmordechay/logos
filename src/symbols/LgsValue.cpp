#include "LgsValue.h"
#include "funcs/LgsFunc.h"
#include "utils/LgsUtils.h"

void LgsValue::startBlock(LgsRuntime* runtime, BasicBlock* const block) const {
    block->insertInto(runtime->IRFunc);
    runtime->builder.SetInsertPoint(block);
}

void LgsValue::startFuncBlock(LgsRuntime* runtime) const {
    const auto entryBlock = BasicBlock::Create(runtime->module->getContext(), "entry", runtime->IRFunc);
    runtime->builder.SetInsertPoint(entryBlock);
}

Value* LgsValue::hashIRValue(LgsRuntime* runtime, Value* value) const {
    const auto hashValueIRFuncType = FunctionType::get(runtime->builder.getInt32Ty(), {runtime->builder.getPtrTy()}, false);
    const auto func =runtime->module->getOrInsertFunction("hash_Str", hashValueIRFuncType);
    return runtime->builder.CreateCall(func, {value});
}

void LgsValue::copyMem(LgsRuntime* runtime, Value* src, Value* dest, const size_t n) const {
    auto& builder = runtime->builder;
    builder.CreateCall(getMemcpy(runtime), {dest, src, builder.getInt64(n), builder.getFalse()});
}

void LgsValue::setLocation(const Token* ctx, path* filePath) {
    location.lineNumber = ctx->getLine();
    location.posInLine = ctx->getCharPositionInLine() + 1;
    location.filePath = filePath;
}

void LgsValue::setIRValue(Value* value) {
    IRValue = value;
}

GlobalVariable* LgsValue::createIRGlobal(const LgsRuntime* runtime, Type* type, Constant* value) const {
    return new GlobalVariable(*runtime->module, type, true, GlobalValue::PrivateLinkage, value);
}

bool LgsValue::shouldLoadIRArg(Value* value, const LgsExpr* expr) const {
    if (expr->isNull || expr->type->asPtr() || expr->type->asStr()) return false;
    if (isa<GlobalVariable>(value) || isa<LoadInst>(value)) return false;
    if (const auto alloca = dyn_cast<AllocaInst>(value)) {
        const auto allocatedType = alloca->getAllocatedType();
        return !allocatedType->isStructTy() && !allocatedType->isArrayTy();
    }
    if (value->getType()->isIntegerTy() || value->getType()->isFloatingPointTy()) {
        return false;
    }
    if (const auto gep = dyn_cast<GetElementPtrInst>(value)) {
        const auto source = gep->getSourceElementType();
        const auto results = gep->getResultElementType();
        const auto isArrayTy = source->isArrayTy();
        const auto isByteTy = results && results->isIntegerTy(8);
        return !isArrayTy || !isByteTy;
    }
    if (isa<ConstantExpr>(value)) {
        const auto constExpr = cast<ConstantExpr>(value);
        return constExpr->getOpcode() == Instruction::GetElementPtr;
    }
    if (isa<Function>(value)) return false;
    return true;
}

string LgsValue::format(string& indentStr) {
    assert(0);
}