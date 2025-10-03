#include "types/iterables/LgsSArray.h"
#include "codegen/LgsLLVMGen.h"
#include "data/LgsDefinitions.h"
#include "exprs/LgsArrayExpr.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsInt.h"

Type* LgsSArray::getIRType(LgsLLVMGen& cg) {
    if (IRType) return IRType;
    const auto innerIRType = baseType->getIRType(cg);
    IRType = ArrayType::get(innerIRType, size->getConstInt());
    return IRType;
}

std::string LgsSArray::getName() {
    const auto ty = baseType ? baseType->pname() : LGS_UNKNOWN_TYPE;
    return ty + '[' + size->getName() + "]";
}

std::string LgsSArray::pname() {
    return getName();
}

size_t LgsSArray::getSizeBytes() {
    return baseType->getSizeBytes() * size->getConstInt();
}

LgsExpr* LgsSArray::getZeroValue() {
    assert(isStatic);
    const auto arrExpr = new LgsArrayExpr(this);
    const auto iterSize = size->getConstInt();
    for (size_t i = 0; i < iterSize; i++) {
        arrExpr->initialElements.push_back(baseType->getZeroValue());
    }
    return arrExpr;
}

Lgs_RTType LgsSArray::getRTType() {
    return RTT_SARRAY;
}

std::string LgsSArray::strFormatPart() const {
    if (baseType->asChar()) return "%s";
    return "%p";
}

LgsType* LgsSArray::applyOp(const LgsOperator op, LgsType* other) {
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

Value* LgsSArray::lengthIR(LgsLLVMGen& cg, Value* iterable) {
    return size->IRValue;
}

Value* LgsSArray::inIR(LgsLLVMGen& cg, LgsExpr* iterableExpr, LgsExpr* value) {
    const auto resultPtr = cg.builder.CreateAlloca(cg.builder.getInt1Ty());
    cg.builder.CreateStore(cg.false_(), resultPtr);
    cg.loop(size->loadIR(cg), [this, &cg, iterableExpr, value, resultPtr](Value* index, BasicBlock* exitBlock) {
        const auto trueBlock = cg.createBlock();
        const auto falseBlock = cg.createBlock();
        const auto zeroValue = baseType->getZeroValue();
        zeroValue->IRValue = getIRElement(cg, iterableExpr->IRValue, index);
        const auto eq = zeroValue->eqIR(cg, value->IRValue);
        cg.builder.CreateCondBr(eq, trueBlock, falseBlock);
        cg.startBlock(trueBlock);
        cg.builder.CreateStore(cg.true_(), resultPtr);
        cg.builder.CreateBr(exitBlock);
        cg.startBlock(falseBlock);
        freeExpr(zeroValue);
    });
    return cg.builder.CreateLoad(cg.builder.getInt1Ty(), resultPtr);
}

Value* LgsSArray::getIRElement(LgsLLVMGen& cg, Value* iterable, Value* index) {
    const auto gep = cg.builder.CreateGEP(getIRType(cg), iterable, {cg.i32Zero(), index});
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

