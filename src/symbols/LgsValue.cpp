#include "LgsValue.h"
#include "funcs/LgsFunc.h"
#include "utils/LgsUtils.h"

void LgsValue::startBlock(LgsModule* module, BasicBlock* const block) const {
    block->insertInto(module->IRFunc);
    module->builder.SetInsertPoint(block);
}

void LgsValue::startFuncBlock(LgsModule* module) const {
    const auto entryBlock = BasicBlock::Create(module->IRModule->getContext(), "entry", module->IRFunc);
    module->builder.SetInsertPoint(entryBlock);
}

Value* LgsValue::hashIRValue(LgsModule* module, Value* value) const {
    const auto hashValueIRFuncType = FunctionType::get(module->builder.getInt32Ty(), {module->builder.getPtrTy()}, false);
    const auto func =module->IRModule->getOrInsertFunction("hash_Str", hashValueIRFuncType);
    return module->builder.CreateCall(func, {value});
}

void LgsValue::copyMem(LgsModule* module, Value* src, Value* dest, const size_t n) const {
    auto& builder = module->builder;
    builder.CreateCall(getMemcpy(module), {dest, src, builder.getInt64(n), builder.getFalse()});
}

void LgsValue::setLocation(const Token* start, const Token* end, path* filePath) {
    location.lineNumberStart = start->getLine();
    location.posInLineStart = start->getCharPositionInLine() + 1;
    if (!end) {
        location.lineNumberEnd = start->getLine();
        location.posInLineEnd = start->getCharPositionInLine() + start->getText().length();
    }
    location.filePath = filePath;
}

void LgsValue::setIRValue(Value* value) {
    IRValue = value;
}

GlobalVariable* LgsValue::createIRGlobal(const LgsModule* module, Type* type, Constant* value) const {
    return new GlobalVariable(*module->IRModule, type, true, GlobalValue::PrivateLinkage, value);
}

bool LgsValue::shouldLoadIRArg(Value* value, const LgsExpr* expr) const {
    if (isa<GlobalVariable>(value) || isa<LoadInst>(value)) return false;
    if (expr->isNull || expr->type->asPtr() || expr->type->asStr()) return false;
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