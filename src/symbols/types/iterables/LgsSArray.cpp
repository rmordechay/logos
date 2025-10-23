#include "types/iterables/LgsSArray.h"
#include "codegen/LgsLLVMGen.h"
#include "exprs/LgsArrayExpr.h"
#include "funcs/LgsFunc.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsBool.h"

Type* LgsSArray::getIRType(LgsLLVMGen& cg) {
    if (IRType) return IRType;
    const auto numElements = size->getConstInt();
    if (numElements) {
        const auto innerIRType = baseType->getIRType(cg);
        IRType = ArrayType::get(innerIRType, *numElements);
    } else {
        IRType = cg.ptrTy();
    }
    return IRType;
}

std::string LgsSArray::getName() {
    return name;
}

std::string LgsSArray::pname() {
    return getName();
}

size_t LgsSArray::getSizeBytes() {
    const auto constInt = size->getConstInt();
    if (!constInt) return 0;
    return baseType->getSizeBytes() * *constInt;
}

LgsExpr* LgsSArray::getZeroValue() {
    assert(isStatic);
    return new LgsArrayExpr(this);
}

Lgs_rttype LgsSArray::getRTType() {
    return RTT_SARRAY;
}

std::string LgsSArray::strFormatPart() const {
    if (baseType->asChar()) return "%s";
    return "%p";
}

LgsType* LgsSArray::applyBinOp(const LgsBinOpType op, LgsType* other) {
    const auto IRName = other->getName();
    switch (op) {
    case IN: {
        if (other->canCastTo(baseType)) return &LGS_BOOL;
        break;
    }
    default:
        break;
    }
    return nullptr;
}

Value* LgsSArray::inIR(LgsLLVMGen& cg, LgsExpr* iterableExpr, LgsExpr* value) {
    const auto resultPtr = cg.builder.CreateAlloca(cg.builder.getInt1Ty());
    cg.builder.CreateStore(cg.false_(), resultPtr);
    cg.loop(size->loadIR(cg), [this, &cg, iterableExpr, value, resultPtr](Value* index, BasicBlock* exitBlock) {
        const auto trueBlock = cg.createBlock();
        const auto falseBlock = cg.createBlock();
        const auto tempExpr = iterableExpr->type->asIterable()->baseType->getZeroValue();
        tempExpr->IRValue = getIRElement(cg, iterableExpr->IRValue, index);
        const auto eq = baseType->eqIR(cg, tempExpr, value);
        cg.builder.CreateCondBr(eq, trueBlock, falseBlock);
        cg.startBlock(trueBlock);
        cg.builder.CreateStore(cg.true_(), resultPtr);
        cg.builder.CreateBr(exitBlock);
        cg.startBlock(falseBlock);
        freeExpr(tempExpr);
    });
    return cg.builder.CreateLoad(cg.builder.getInt1Ty(), resultPtr);
}

Value* LgsSArray::getIRElement(LgsLLVMGen& cg, Value* iterable, Value* index) {
    const auto gep = cg.builder.CreateGEP(getIRType(cg), iterable, {cg.i32Zero(), index});
    return cg.builder.CreateLoad(baseType->getIRType(cg), gep);
}

Value* LgsSArray::lengthIR(LgsLLVMGen& cg, Value* iterable) {
    return size->IRValue;
}

LgsFunc* LgsSArray::getLenFunc() {
    const auto lenFunc = LgsIterable::getLenFunc();
    if (lenFunc->fn) return lenFunc;
    lenFunc->fn = [this](LgsLLVMGen& cg, const std::vector<LgsExpr*>& args) {
        return cg.extendToSize(size->IRValue);
    };
    return lenFunc;
}

bool LgsSArray::canCastTo(LgsType* other) {
    if (!baseType) return false;
    if (other->getName() == LgsAny::name) return true;
    const auto otherArr = other->asIterable();
    if (!otherArr) return false;
    return baseType->canCastTo(otherArr->baseType);
}
