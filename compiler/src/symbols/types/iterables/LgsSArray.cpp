#include "types/iterables/LgsSArray.h"
#include "codegen/LgsCgModule.h"
#include "exprs/LgsArrayExpr.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsBool.h"
#include "Lgs_Exprs.h"
#include "exprs/LgsBinaryExpr.h"
#include "lgsc/LgsCCompiler.h"
#include "types/LgsPtr.h"
#include "types/iterables/LgsStr.h"

Type* LgsSArray::getIRType(LgsCgModule& cg) {
    const auto innerIRType = baseType->getIRType(cg);
    return ArrayType::get(innerIRType, length->getConstInt().value());
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
    return baseType->sizeBytes() * length->getConstInt().value();
}

LgsExpr* LgsSArray::getZeroValue() {
    assert(isStatic);
    return new LgsArrayExpr(this);
}

Constant* LgsSArray::getRTType(LgsCgModule& cg) {
    const auto sArrName = getName();
    const auto sArrSize = length->getConstInt().value();
    const std::vector<Constant*> args = {cg.usize(sArrSize), baseType->getRTType(cg)};
    const auto sv = cg.getRTTExtraStruct(sArrName, {cg.sizeTy(), cg.ptrTy()}, args);
    return cg.getRTTypeInfo(sArrName, IRSize(cg), RTT_SARRAY, isHeapAlloc, sv);
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
            return new LgsSArray(baseType, new LgsBinaryExpr(length, otherSArr->length, ADD_OP));
        }
    }
    default:
        break;
    }
    return nullptr;
}

bool LgsSArray::inferBaseType(std::vector<LgsExpr*>& args) {
    if (baseType) return true;
    assert(!args.empty());
    const auto baseExprType = args.front()->type;
    for (size_t i = 1; i < args.size(); ++i) {
        const auto arg = args[i];
        if (!arg->type->canCastTo(baseExprType)) return false;
    }
    baseType = baseExprType;
    return true;
}

Value* LgsSArray::addIR(LgsCgModule& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    const auto baseIR = baseType->getIRType(cg);
    const auto leftSArr = left->type->asSArray();
    const auto rightSArr = right->type->asSArray();
    const auto leftSize = leftSArr->length->loadIR(cg);
    const auto rightSize = rightSArr->length->loadIR(cg);

    const auto newSize = cg.builder.CreateAdd(leftSize, rightSize);
    const auto newArr = cg.builder.CreateAlloca(baseIR, newSize);
    const auto sizeLeft = cg.builder.CreateMul(leftSize, cg.i32(baseType->IRSize(cg)));
    cg.callMemcpy(newArr, left->IRValue, sizeLeft);
    const auto sizeRight = cg.builder.CreateMul(rightSize, cg.i32(baseType->IRSize(cg)));
    const auto offset = cg.builder.CreateInBoundsGEP(baseIR, newArr, leftSize);
    cg.callMemcpy(offset, right->IRValue, sizeRight);
    return newArr;
}

Value* LgsSArray::mulIR(LgsCgModule& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    const auto arrPtr = left->IRValue;
    const auto arrSize = cg.extendToSize(left->type->asSArray()->length->IRValue);
    const auto multiplier = cg.extendToSize(right->IRValue);
    const auto newSize = cg.builder.CreateMul(arrSize, multiplier);
    const auto newArr = cg.builder.CreateAlloca(baseType->getIRType(cg), newSize);
    const auto bytesPerCopy = cg.builder.CreateMul(arrSize, cg.usize(baseType->IRSize(cg)));
    cg.loop(multiplier, [&](Value* i, BasicBlock*) {
        const auto offset = cg.builder.CreateMul(i, arrSize);
        const auto destPtr = cg.builder.CreateInBoundsGEP(baseType->getIRType(cg), newArr, offset);
        cg.callMemcpy(destPtr, arrPtr, bytesPerCopy);
    });
    return newArr;
}

Value* LgsSArray::inIR(LgsCgModule& cg, Value* iterableExpr, Value* value) {
    const auto resultPtr = cg.builder.CreateAlloca(cg.builder.getInt1Ty());
    cg.store(cg.false_(), resultPtr);
    cg.loop(length->loadIR(cg), [this, &cg, iterableExpr, value, resultPtr](Value* index, BasicBlock* exitBlock) {
        const auto trueBlock = cg.createBlock();
        const auto falseBlock = cg.createBlock();
        const auto element = getIRElement(cg, iterableExpr, index);
        const auto eq = eqIR(cg, element, value, baseType);
        cg.builder.CreateCondBr(eq, trueBlock, falseBlock);
        cg.startBlock(trueBlock);
        cg.store(cg.true_(), resultPtr);
        cg.builder.CreateBr(exitBlock);
        cg.startBlock(falseBlock);
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
    return length->IRValue;
}

bool LgsSArray::canCastTo(LgsType* other) {
    if (!baseType) return false;
    if (other->isAny()) return true;
    if (other->asStr()) return !!baseType->asChar();
    const auto otherIter = other->asIterable();
    if (!otherIter) return false;
    return baseType->canCastTo(otherIter->baseType);
}

bool LgsSArray::equals(LgsType* other) {
    if (baseType->asChar() && other->asStr()) return true;
    const auto otherArr = other->asSArray();
    if (!otherArr) return false;
    if (!baseType->equals(otherArr->baseType)) return false;
    const auto constSize = length->getConstInt().value();
    const auto otherConstSize = otherArr->length->getConstInt();
    return constSize == otherConstSize.value();
}

DIType* LgsSArray::getDebugType(LgsCgModule& cg) {
    assert(0);
}
