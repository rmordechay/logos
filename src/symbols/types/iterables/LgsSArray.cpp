#include "types/iterables/LgsSArray.h"

#include "codegen/LgsLLVMGen.h"
#include "data/LgsDefinitions.h"
#include "exprs/LgsArrayExpr.h"
#include "exprs/LgsIterIndex.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsSize.h"

Type* LgsSArray::getIRType(LgsLLVMGen& cg) {
    if (IRType) return IRType;
    const auto innerIRType = baseType->getIRType(cg);
    IRType = ArrayType::get(innerIRType, sizeExpr->getConstInt());
    return IRType;
}

std::string LgsSArray::getName() {
    return name;
}

std::string LgsSArray::pname() {
    const auto index = sizeExpr->getConstInt() == 0 ? "" : std::to_string(sizeExpr->getConstInt());
    const auto ty = baseType ? baseType->pname() : LGS_UNKNOWN_TYPE;
    return ty + '[' + index + "]!";
}

size_t LgsSArray::getSizeBytes() {
    return baseType->getSizeBytes() * sizeExpr->getConstInt();
}

LgsExpr* LgsSArray::getZeroValue() {
    return new LgsArrayExpr(this);
}

Lgs_RTType LgsSArray::getRTType() {
    return RTT_SARRAY;
}

LgsType* LgsSArray::getIndexType() {
    return &LGS_INT;
}

uint16_t LgsSArray::getUnpackCount() const {
    return 1;
}

std::string LgsSArray::strFormatPart() const {
    if (baseType->asChar()) return "%s";
    return "%p";
}

LgsType* LgsSArray::applyOp(LgsType* other, const LgsOperator op) {
    const auto IRName = other->getName();
    switch (op) {
    case IN: {
        if (other->canCastTo(baseType)) return baseType;
        break;
    }
    default:
        break;
    }
    return nullptr;
}

Value* LgsSArray::lengthIR(LgsLLVMGen& cg, Value* iterable) {
    return sizeExpr->IRValue;
}

Value* LgsSArray::inIR(LgsLLVMGen& cg, LgsExpr* iterableExpr, LgsExpr* value) {
    const auto resultPtr = cg.builder.CreateAlloca(cg.builder.getInt1Ty());
    cg.builder.CreateStore(cg.false_(), resultPtr);
    cg.loop(sizeExpr->loadIR(cg), [this, &cg, iterableExpr, value, resultPtr](Value* index, BasicBlock* exitBlock) {
        const auto trueBlock = cg.createBlock();
        const auto falseBlock = cg.createBlock();
        const auto e = getIRElement(cg, iterableExpr->IRValue, index);
        const auto eq = baseType->eqIR(cg, e, value->loadIR(cg));
        cg.builder.CreateCondBr(eq, trueBlock, falseBlock);
        cg.startBlock(trueBlock);
        cg.builder.CreateStore(cg.true_(), resultPtr);
        cg.builder.CreateBr(exitBlock);
        cg.startBlock(falseBlock);
    });
    return cg.builder.CreateLoad(cg.builder.getInt1Ty(), resultPtr);
}

Value* LgsSArray::getIRElement(LgsLLVMGen& cg, Value* iterable, Value* index) {
    const auto gep =  cg.builder.CreateGEP(getIRType(cg), iterable, {cg.i32Zero(), index});
    return cg.builder.CreateLoad(baseType->getIRType(cg), gep);
}

bool LgsSArray::canCastTo(LgsType* other) {
    if (!baseType) return false;
    if (other->getName() == LgsAny::name) return true;
    const auto otherArr = other->asIterable();
    if (!otherArr) return false;
    return baseType->canCastTo(otherArr->baseType);
}

json::value LgsSArray::asJsonStr() {
    assert(0);
}

