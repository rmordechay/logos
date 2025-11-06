#include "types/iterables/LgsSArray.h"
#include "codegen/LgsLLVMGen.h"
#include "exprs/LgsArrayExpr.h"
#include "funcs/LgsFunc.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsBool.h"
#include "utils/LgsUtils.h"

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
    if (baseType) return baseType->pname() + "[]";
    return "[]";;
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

Lgs_RTType LgsSArray::getRTType() {
    return RTT_SARRAY;
}

std::string LgsSArray::strFormatPart() const {
    if (baseType->asChar()) return "%s";
    return "%p";
}

LgsType* LgsSArray::applyBinOp(LgsBinaryExpr* binExpr) {
    const auto r = binExpr->right;
    const auto op = binExpr->op;
    const auto IRName = r->type->getName();
    switch (op) {
    case IN: {
        if (r->type->canCastTo(baseType)) return &LGS_BOOL;
        break;
    }
    case ADD: {
        const auto otherSArr = r->type->asIterable();
        if (baseType->canCastTo(otherSArr->baseType)) {
            const auto sumSize = new LgsBinaryExpr(size, otherSArr->size, ADD_OP);
            return new LgsSArray(baseType, sumSize);
        }
    }
    case MUL: {
        if (r->type->isInt) {
            const auto mulSize = new LgsBinaryExpr(size, r, MUL_OP);
            return new LgsSArray(baseType, mulSize);
        }
    }
    default:
        break;
    }
    return nullptr;
}

Value* LgsSArray::addIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto otherSArr = other->type->asSArray();
    const auto sizeNewArr = cg.builder.CreateAdd(size->IRValue, otherSArr->size->IRValue);
    const auto newArr = cg.builder.CreateAlloca(baseType->getIRType(cg), sizeNewArr);
    const auto size1 = cg.builder.CreateMul(size->IRValue, cg.i32(baseType->getSizeBytes()));
    const auto size2 = cg.builder.CreateMul(otherSArr->size->IRValue, cg.i32(baseType->getSizeBytes()));
    cg.callMemCpy(newArr, self->IRValue, size1);
    const auto offset = cg.builder.CreateInBoundsGEP(baseType->getIRType(cg), newArr, size->IRValue);
    cg.callMemCpy(offset, other->IRValue, size2);
    return newArr;
}

Value* LgsSArray::mulIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto arrPtr = self->IRValue;
    const auto arrSize = cg.extendToSize(self->type->asSArray()->size->IRValue);
    const auto multiplier = cg.extendToSize(other->IRValue);
    const auto newSize = cg.builder.CreateMul(arrSize, multiplier);
    const auto newArr = cg.builder.CreateAlloca(baseType->getIRType(cg), newSize);
    const auto bytesPerCopy = cg.builder.CreateMul(arrSize, cg.usize(baseType->getSizeBytes()));
    cg.loop(multiplier, [&](Value* i, BasicBlock*) {
        const auto offset = cg.builder.CreateMul(i, arrSize);
        const auto destPtr = cg.builder.CreateInBoundsGEP(baseType->getIRType(cg), newArr, offset);
        cg.callMemCpy(destPtr, arrPtr, bytesPerCopy);
    });
    return newArr;
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
    lenFunc->fn = [this](LgsLLVMGen& cg, const std::vector<LgsExpr*>&) {
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

LgsType* LgsSArray::clone() {
    return new LgsSArray(baseType->clone(), size->cloneExpr());
}
