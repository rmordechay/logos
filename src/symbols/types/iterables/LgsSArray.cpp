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

size_t LgsSArray::sizeBytes() {
    const auto constInt = size->getConstInt();
    if (!constInt) return 0;
    return baseType->sizeBytes() * *constInt;
}

LgsExpr* LgsSArray::getZeroValue() {
    assert(isStatic);
    return new LgsArrayExpr(this);
}

Lgs_TypeKind LgsSArray::getRTTypeKind() {
    if (baseType->asChar()) return RTT_STR;
    return RTT_SARRAY;
}

Constant* LgsSArray::getRTType(LgsLLVMGen& cg) {
    assert(size->IRValue);
    const auto arrRTStruct = cg.getStructType({cg.i32Ty(), cg.sizeTy()}, LGS_RT_ARRAY);
    const auto sizeValue = size->loadIR(cg);
    const auto rttKind = baseType->getRTTypeKind();
    const std::vector<Constant*> structFields = {cg.i32(rttKind), llvm::dyn_cast<Constant>(sizeValue)};
    return llvm::ConstantStruct::get(arrRTStruct, structFields);
}

std::string LgsSArray::strFormatPart() const {
    if (baseType->asChar()) return "%s";
    return "%p";
}

LgsType* LgsSArray::applyBinOp(LgsBinaryExpr* binExpr) {
    const auto r = binExpr->right;
    const auto [opType, text] = binExpr->op;
    switch (opType) {
    case IN: {
        if (r->type->canCastTo(baseType)) return &LGS_BOOL;
        break;
    }
    case ADD: {
        if (const auto otherSArr = r->type->asSArray()) {
            if (!baseType->canCastTo(otherSArr->baseType)) break;
            return new LgsSArray(baseType, new LgsBinaryExpr(size, otherSArr->size, ADD_OP));
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

Value* LgsSArray::addIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
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

Value* LgsSArray::mulIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto arrPtr = self->IRValue;
    const auto arrSize = cg.extendToSize(self->type->asSArray()->size->IRValue);
    const auto multiplier = cg.extendToSize(other->IRValue);
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
    lenFunc->fn = [this](LgsLLVMGen& cg, const std::vector<LgsFuncArg>&) {
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
    return new LgsSArray(baseType->clone(), size->clone());
}
