#include "types/LgsNullable.h"

#include "LgsBinaryTokens.h"
#include "LgsDefinitions.h"
#include "codegen/LgsCodeGen.h"
#include "exprs/LgsExpr.h"
#include "exprs/LgsNullableExpr.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsBool.h"
#include <cassert>
#include <llvm/IR/Module.h>

#include "exprs/LgsBinaryExpr.h"

LgsField* LgsNullable::getField(const std::string& fieldName) {
    return baseType->getField(fieldName);
}

LgsFunc* LgsNullable::getMethod(const std::string& methodName) {
    return baseType->getMethod(methodName);
}

size_t LgsNullable::sizeBytes() {
    if (passByRef) return sizeof(void*);
    return baseType->sizeBytes() + sizeof(bool);
}

LgsExpr* LgsNullable::getZeroValue() {
    return new LgsNullableExpr();
}

Value* LgsNullable::getIRZeroValue(LgsCodeGen& cg, Value* pointee) {
    return cg.null();
}

std::string LgsNullable::pname() {
    return baseType ? baseType->pname() + '?' : name;
}

std::string LgsNullable::getName() {
    if (passByRef) return baseType ? baseType->getName(): name;
    return baseType ? baseType->getName() + name : name;
}

Type* LgsNullable::getIRType(LgsCodeGen& cg) {
    if (passByRef) return cg.ptrTy();
    return cg.getStructType({baseType->getIRType(cg), cg.i1Ty()}, getName());
}

Constant* LgsNullable::getRTTypeExtra(LgsCodeGen& cg) {
    if (passByRef) return baseType->getRTType(cg);
    return baseType->getRTType(cg);
}

bool LgsNullable::canCastTo(LgsType* other) {
    if (other->isAny()) return true;
    if (isNull) return false;
    const auto otherNullable = other->asNullable();
    if (!otherNullable) return false;
    return baseType->canCastTo(otherNullable->baseType);
}

std::string LgsNullable::fmtStr() const {
    assert(0);
}

DIType* LgsNullable::getDebugType(LgsCodeGen& cg) {
    assert(0);
}

LgsType* LgsNullable::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    const auto toNullable = rightType->asNullable();
    if (!toNullable) return nullptr;
    switch (op.opType) {
    case EQ:
    case NE: {
        if (!baseType || !toNullable->baseType) return &LGS_BOOL;
        if (baseType->canCastTo(toNullable->baseType)) return &LGS_BOOL;
        break;
    }
    case ADD:
    case SUB:
    case MUL:
    case MODULO:
    case BIT_AND:
    case BIT_OR:
    case BIT_XOR:
    case LSHIFT:
    case RSHIFT: {
        if (!baseType) return nullptr;
        return new LgsNullable(baseType->applyBinOp(toNullable->baseType, op));
    }
    default:
        assert(0);
    }
    return nullptr;
}

Value* LgsNullable::addIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    const auto f = [this, &cg](LgsBinaryExpr* e) {return baseType->addIR(cg, e);};
    return passByRef ? applyPtrBinOp(cg, binExpr, f) : applyNumberBinOp(cg, binExpr, f);
}

void LgsNullable::setIRFields(LgsCodeGen& cg, Value* ptr, Value* value, Value* isSet) {
    const auto ty = getIRType(cg);
    cg.storeStructField(ty, ptr, LgsNullableExprIndices::value, value);
    cg.storeStructField(ty, ptr, LgsNullableExprIndices::isSet, isSet);
}

Value* LgsNullable::loadIsSet(LgsCodeGen& cg, Value* ptr) {
    return cg.loadStructField(getIRType(cg), ptr, LgsNullableExprIndices::isSet, cg.i1Ty());
}

Value* LgsNullable::applyNumberBinOp(LgsCodeGen& cg, LgsBinaryExpr* binExpr, const std::function<Value*(LgsBinaryExpr*)>& func) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    const auto ty = getIRType(cg);
    const auto ptr = cg.builder.CreateAlloca(ty);
    const auto leftNullable = left->type->asNullable();
    const auto rightNullable = right->type->asNullable();
    const auto addBlock = cg.createBlock();
    const auto nullBlock = cg.createBlock();
    const auto exitBlock = cg.createBlock();

    const auto isSet1 = leftNullable->loadIsSet(cg, left->IRValue);
    const auto isSet2 = rightNullable->loadIsSet(cg, right->IRValue);
    const auto bothSet = cg.builder.CreateAnd(isSet1, isSet2);
    cg.builder.CreateCondBr(bothSet, addBlock, nullBlock);

    cg.startBlock(addBlock);
    const auto result = func(binExpr);
    setIRFields(cg, ptr, result, cg.true_());
    cg.builder.CreateBr(exitBlock);

    cg.startBlock(nullBlock);
    cg.storeStructField(ty, ptr, LgsNullableExprIndices::isSet, cg.false_());
    cg.builder.CreateBr(exitBlock);

    cg.startBlock(exitBlock);
    return ptr;
}

Value* LgsNullable::applyPtrBinOp(LgsCodeGen& cg, LgsBinaryExpr* binExpr, const std::function<Value*(LgsBinaryExpr*)>& func) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    const auto ptr = cg.builder.CreateAlloca(getIRType(cg));
    const auto leftNotNull = cg.builder.CreateIsNotNull(left->IRValue);
    const auto rightNotNull = cg.builder.CreateIsNotNull(right->IRValue);
    const auto bothNotNull = cg.builder.CreateAnd(leftNotNull, rightNotNull);
    const auto addBlock = cg.createBlock();
    const auto nullBlock = cg.createBlock();
    const auto exitBlock = cg.createBlock();
    cg.builder.CreateCondBr(bothNotNull, addBlock, nullBlock);

    cg.startBlock(addBlock);
    const auto result = func(binExpr);
    cg.store(result, ptr);
    cg.builder.CreateBr(exitBlock);

    cg.startBlock(nullBlock);
    cg.store(cg.null(), ptr);
    cg.builder.CreateBr(exitBlock);

    cg.startBlock(exitBlock);
    return ptr;
}
