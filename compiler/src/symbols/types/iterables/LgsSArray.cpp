#include "types/iterables/LgsSArray.h"
#include <llvm/IR/Module.h>
#include "codegen/LgsCodeGen.h"
#include "exprs/LgsArrayExpr.h"
#include "types/primitives/LgsBool.h"
#include "exprs/LgsBinaryExpr.h"
#include "lgsc/LgsCCompiler.h"
#include "types/iterables/LgsStr.h"

Type* LgsSArray::getIRType(LgsCodeGen& cg) {
    return ArrayType::get(baseType->getIRType(cg), len);
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
    return baseType->sizeBytes() * len;
}

LgsExpr* LgsSArray::getZeroValue() {
    return new LgsArrayExpr(this);
}

Constant* LgsSArray::getRTType(LgsCodeGen& cg) {
    const auto RTTName = LGS_TYPEINFO_PREFIX + getName() + std::to_string(len);
    if (const auto v = cg.IRModule->getGlobalVariable(RTTName)) return v;
    if (cg.mode != CG_MODE_RTTYPES) return cg.createGlobal(RTTName, cg.getRTTStructType(), nullptr);
    const auto st = cg.getStructType({cg.sizeTy(), cg.ptrTy()});
    const auto baseTypeRTT = cg.getRTTypeInfo(baseType->getName(), baseType->IRSize(cg), baseType->rtt);
    const std::vector<Constant*> args = {cg.usize(len), baseTypeRTT};
    return cg.createGlobal(RTTName, st, ConstantStruct::get(st, args));
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
            return new LgsSArray(baseType, new LgsBinaryExpr(lengthExpr, otherSArr->lengthExpr, ADD_OP));
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

Value* LgsSArray::inIR(LgsCodeGen& cg, Value* iterableExpr, Value* value) {
    const auto resultPtr = cg.builder.CreateAlloca(cg.builder.getInt1Ty());
    cg.store(cg.false_(), resultPtr);
    cg.loop(cg.usize(len), [this, &cg, iterableExpr, value, resultPtr](Value* index, BasicBlock* exitBlock) {
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

Value* LgsSArray::getIRElement(LgsCodeGen& cg, Value* iterable, Value* index) {
    const auto gep = cg.builder.CreateGEP(getIRType(cg), iterable, {cg.i32Zero(), index});
    return cg.load(baseType->getIRType(cg), gep);
}

void LgsSArray::addIRElement(LgsCodeGen& cg, Value* iterable, Value* index, Value* value) {
    const std::vector<Value*> indices = {cg.i32Zero(), index};
    const auto gep = cg.builder.CreateInBoundsGEP(getIRType(cg), iterable, indices);
    cg.store(value, gep);
}

Value* LgsSArray::lenIR(LgsCodeGen& cg, Value* iterable) {
    return cg.usize(len);
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
    return len == otherArr->len;
}

DIType* LgsSArray::getDebugType(LgsCodeGen& cg) {
    assert(0);
}
