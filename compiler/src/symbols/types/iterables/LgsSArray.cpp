#include "types/iterables/LgsSArray.h"
#include "codegen/LgsCgModule.h"
#include "exprs/LgsArrayExpr.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsBool.h"
#include "Lgs_DArrayExpr.h"
#include "exprs/LgsBinaryExpr.h"
#include "lgsc/LgsCCompiler.h"

Type* LgsSArray::getIRType(LgsCgModule& cg) {
    if (IRType) return IRType;
    const auto innerIRType = baseType->getIRType(cg);
    IRType = ArrayType::get(innerIRType, size->getConstInt().value());
    return IRType;
}

std::string LgsSArray::getBaseName() {
    return name;
}

std::string LgsSArray::getName() {
    return name + baseType->getName();
}

std::string LgsSArray::pname() {
    if (baseType) return baseType->pname() + "[]";
    return "[]";;
}

size_t LgsSArray::sizeBytes() {
    return baseType->sizeBytes() * size->getConstInt().value();
}

LgsExpr* LgsSArray::getZeroValue() {
    assert(isStatic);
    return new LgsArrayExpr(this);
}

Value* LgsSArray::getIRZeroValue(LgsCgModule& cg, Value* pointee) {
    const auto ty = getIRType(cg);
    const auto arrSize = size->getConstInt().value();
    const auto arr = pointee ? pointee : cg.builder.CreateAlloca(ty);
    for (int64_t i = 0; i < arrSize; ++i) {
        addIRElement(cg, arr, cg.i32(i), baseType->getIRZeroValue(cg));
    }
    return arr;
}

Constant* LgsSArray::getRTType(LgsCgModule& cg) {
    const auto sArrName = getName();
    const auto sArrSize = size->getConstInt().value();
    const std::vector<Constant*> args = {cg.usize(sArrSize), baseType->getRTType(cg)};
    const auto sv = cg.getRTTExtraStruct(sArrName, {cg.sizeTy(), cg.ptrTy()}, args);
    return cg.getRTTypeInfo(sArrName, sizeBytes(), RTT_SARRAY, isHeapAlloc, sv);
}

std::string LgsSArray::fmtStr() const {
    if (baseType->asChar()) return "%s";
    return "%p";
}

LgsType* LgsSArray::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    switch (op.opType) {
    case IN: {
        if (rightType->canCastTo(baseType)) return &LGS_BOOL;
        break;
    }
    case ADD: {
        if (const auto otherSArr = rightType->asSArray()) {
            if (!baseType->canCastTo(otherSArr->baseType)) break;
            return new LgsSArray(baseType, new LgsBinaryExpr(size, otherSArr->size, ADD_OP));
        }
    }
    default:
        break;
    }
    return nullptr;
}

bool LgsSArray::inferBaseType(std::vector<LgsExpr*>& args) {
    assert(0);
}

Value* LgsSArray::addIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto baseIR = baseType->getIRType(cg);
    const auto leftSArr = left->type->asSArray();
    const auto rightSArr = right->type->asSArray();
    const auto leftSize = leftSArr->size->loadIR(cg);
    const auto rightSize = rightSArr->size->loadIR(cg);

    const auto newSize = cg.builder.CreateAdd(leftSize, rightSize);
    const auto newArr = cg.builder.CreateAlloca(baseIR, newSize);
    const auto sizeLeft = cg.builder.CreateMul(leftSize, cg.i32(baseType->sizeBytes()));
    cg.callMemCpy(newArr, left->IRValue, sizeLeft);
    const auto sizeRight = cg.builder.CreateMul(rightSize, cg.i32(baseType->sizeBytes()));
    const auto offset = cg.builder.CreateInBoundsGEP(baseIR, newArr, leftSize);
    cg.callMemCpy(offset, right->IRValue, sizeRight);
    return newArr;
}

Value* LgsSArray::mulIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto arrPtr = left->IRValue;
    const auto arrSize = cg.extendToSize(left->type->asSArray()->size->IRValue);
    const auto multiplier = cg.extendToSize(right->IRValue);
    const auto newSize = cg.builder.CreateMul(arrSize, multiplier);
    const auto newArr = cg.builder.CreateAlloca(baseType->getIRType(cg), newSize);
    const auto bytesPerCopy = cg.builder.CreateMul(arrSize, cg.usize(baseType->sizeBytes()));
    cg.loop(multiplier, [&](Value* i, BasicBlock*) {
        const auto offset = cg.builder.CreateMul(i, arrSize);
        const auto destPtr = cg.builder.CreateInBoundsGEP(baseType->getIRType(cg), newArr, offset);
        cg.callMemCpy(destPtr, arrPtr, bytesPerCopy);
    });
    return newArr;
}

Value* LgsSArray::inIR(LgsCgModule& cg, LgsExpr* iterableExpr, LgsExpr* value) {
    const auto resultPtr = cg.builder.CreateAlloca(cg.builder.getInt1Ty());
    cg.store(cg.false_(), resultPtr);
    cg.loop(size->loadIR(cg), [this, &cg, iterableExpr, value, resultPtr](Value* index, BasicBlock* exitBlock) {
        const auto trueBlock = cg.createBlock();
        const auto falseBlock = cg.createBlock();
        const auto tempExpr = iterableExpr->type->asIterable()->baseType->getZeroValue();
        tempExpr->IRValue = getIRElement(cg, iterableExpr->IRValue, index);
        const auto eq = eqIR(cg, tempExpr, value);
        cg.builder.CreateCondBr(eq, trueBlock, falseBlock);
        cg.startBlock(trueBlock);
        cg.store(cg.true_(), resultPtr);
        cg.builder.CreateBr(exitBlock);
        cg.startBlock(falseBlock);
        freeExpr(tempExpr);
    });
    return cg.load(cg.builder.getInt1Ty(), resultPtr);
}

Value* LgsSArray::getIRElement(LgsCgModule& cg, Value* iterable, Value* index) {
    const auto gep = cg.builder.CreateGEP(getIRType(cg), iterable, {cg.i32Zero(), index});
    return cg.load(baseType->getIRType(cg), gep);
}

void LgsSArray::addIRElement(LgsCgModule& cg, Value* iterable, Value* index, Value* value) {
    const std::vector<Value*> indices = {cg.i32Zero(), index};
    const auto gep = cg.builder.CreateInBoundsGEP(getIRType(cg), iterable, indices);
    cg.store(value, gep);
}

Value* LgsSArray::lenIR(LgsCgModule& cg, Value* iterable) {
    return size->IRValue;
}

bool LgsSArray::canCastTo(LgsType* other) {
    if (!baseType) return false;
    if (other->getName() == LgsAny::name) return true;
    const auto otherArr = other->asIterable();
    if (!otherArr) return false;
    return baseType->canCastTo(otherArr->baseType);
}

bool LgsSArray::equals(LgsType* other) {
    if (baseType->asChar() && other->asStr()) return true;
    const auto otherArr = other->asSArray();
    if (!otherArr) return false;
    if (!baseType->equals(otherArr->baseType)) return false;
    const auto constSize = size->getConstInt().value();
    const auto otherConstSize = otherArr->size->getConstInt();
    return constSize == otherConstSize.value();
}

DIType* LgsSArray::getDebugType(LgsCgModule& cg) {
    assert(0);
}
