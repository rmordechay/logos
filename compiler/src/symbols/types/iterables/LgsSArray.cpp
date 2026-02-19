#include "types/iterables/LgsSArray.h"
#include <llvm/IR/Module.h>
#include "codegen/LgsCodeGen.h"
#include "exprs/LgsArrayExpr.h"
#include "types/primitives/LgsBool.h"
#include "exprs/LgsBinaryExpr.h"
#include "lgsc/LgsCCompiler.h"
#include "types/iterables/LgsStr.h"

std::string LgsSArray::getBaseName() {
    return name;
}

std::string LgsSArray::getName() {
    if (len <= 0) return "";
    return name + std::to_string(len) + "_" +  baseType->getName();
}

std::string LgsSArray::pname() {
    if (baseType) return baseType->pname() + "[" + std::to_string(len) + "]";
    return "[" + std::to_string(len) + "]";
}

size_t LgsSArray::sizeBytes() {
    return baseType->sizeBytes() * len;
}

std::string LgsSArray::fmtStr() const {
    if (baseType->asChar()) return "%s";
    return "%p";
}

std::optional<int64_t> LgsSArray::getConstLength() {
    return len;
}

bool LgsSArray::canCastTo(LgsType* other) {
    if (!baseType) return false;
    if (other->isAny()) return true;
    if (other->asStr()) return !!baseType->asChar();
    const auto otherIter = other->asSArray();
    if (!otherIter) return false;
    return baseType->canCastTo(otherIter->baseType);
}

bool LgsSArray::equals(LgsType* other) {
    if (baseType->asChar() && other->asStr()) return true;
    const auto otherArr = other->asSArray();
    if (!otherArr) return false;
    if (!baseType->equals(otherArr->baseType)) return false;
    return len == otherArr->len;
}

LgsExpr* LgsSArray::getZeroValue() {
    return new LgsArrayExpr(this);
}

Value* LgsSArray::getIRZeroValue(LgsCodeGen& cg, Value* pointee) {
    if (pointee) return pointee;
    return cg.builder.CreateAlloca(getIRType(cg));
}

Type* LgsSArray::getIRType(LgsCodeGen& cg) {
    return ArrayType::get(baseType->getIRType(cg), len);
}

LgsType* LgsSArray::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    switch (op.opType) {
    case EQ:
    case NE: {
        const auto otherDarr = rightType->asSArray();
        if (!otherDarr) return nullptr;
        if (otherDarr->baseType->canCastTo(baseType)) return &LGS_BOOL;
        break;
    }
    case IN: {
        if (rightType->canCastTo(baseType)) return &LGS_BOOL;
        break;
    }
    case ADD: {
        if (const auto otherSArr = rightType->asSArray()) {
            if (!baseType->canCastTo(otherSArr->baseType)) break;
            const auto rSize = otherSArr->lengthExpr->getConstInt();
            if (!rSize.has_value()) return nullptr;
            return new LgsSArray(baseType, len + rSize.value());
        }
    }
    default:
        break;
    }
    return nullptr;
}

Constant* LgsSArray::getRTTypeExtra(LgsCodeGen& cg) {
    assert(len > 0);
    const auto rttName = getRTTName() + "_extra";
    const auto st = cg.getStructType({cg.sizeTy(), cg.ptrTy()}, rttName);
    const std::vector<Constant*> args = {cg.usize(len), baseType->getRTType(cg)};
    return cg.createGlobal(rttName, st, ConstantStruct::get(st, args));
}

Value* LgsSArray::addIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    const auto baseIR = baseType->getIRType(cg);
    const auto leftSArr = left->type->asSArray();
    const auto rightSArr = right->type->asSArray();
    const auto leftSize = cg.usize(leftSArr->len);
    const auto rightSize = cg.usize(rightSArr->len);

    const auto newSize = cg.builder.CreateAdd(leftSize, rightSize);
    const auto newArr = cg.builder.CreateAlloca(baseIR, newSize);
    const auto sizeLeft = cg.builder.CreateMul(leftSize, baseType->IRSize(cg));
    cg.callMemcpy(newArr, left->IRValue, sizeLeft);
    const auto sizeRight = cg.builder.CreateMul(rightSize, baseType->IRSize(cg));
    const auto offset = cg.builder.CreateInBoundsGEP(baseIR, newArr, leftSize);
    cg.callMemcpy(offset, right->IRValue, sizeRight);
    return newArr;
}

Value* LgsSArray::lenIR(LgsCodeGen& cg, Value* iterable) {
    return cg.usize(len);
}

Value* LgsSArray::inIR(LgsCodeGen& cg, Value* iterable, Value* value) {
    return cg.builder.CreateCall(getEqFunc(cg), {iterable, value});
}

Value* LgsSArray::getIRElement(LgsCodeGen& cg, Value* iterable, Value* index) {
    assert(iterable);
    return cg.builder.CreateGEP(getIRType(cg), iterable, {cg.zero32(), index});
}

void LgsSArray::addIRElement(LgsCodeGen& cg, Value* iterable, Value* index, Value* value) {
    cg.store(value, getIRElement(cg, iterable, index));
}

Function* LgsSArray::getEqFunc(LgsCodeGen& cg) {
    const auto funcName = getName() + "_" + EQUAL_FUNC;
    if (const auto func = cg.IRModule->getFunction(funcName)) return func;
    const auto ft = cg.getFT(cg.i1Ty(), {cg.ptrTy(), cg.ptrTy()});
    if (cg.mode == CG_MODE_SRC) return cg.getFunc(funcName, ft);

    const auto func = cg.getFunc(funcName, ft);
    cg.savedIP = cg.builder.saveIP();
    cg.startFunc(func);

    const auto arrIR1 = func->getArg(0);
    const auto arrIR2 = func->getArg(1);
    const auto len1 = lenIR(cg, arrIR1);
    const auto len2 = lenIR(cg, arrIR2);
    cg.ifStmt(cg.builder.CreateICmpNE(len1, len2), [&cg] {cg.builder.CreateRet(cg.false_());});

    cg.builder.CreateRet(cg.true_());
    cg.builder.restoreIP(cg.savedIP);
    return func;
}

DIType* LgsSArray::getDebugType(LgsCodeGen& cg) {
    assert(0);
}
