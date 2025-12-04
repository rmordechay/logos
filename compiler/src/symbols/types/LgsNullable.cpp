#include "types/LgsNullable.h"

#include "codegen/LgsCgModule.h"
#include "exprs/LgsExpr.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsBool.h"
#include <cassert>

size_t LgsNullable::sizeBytes() {
    if (passByRef) return sizeof(void*);
    return baseType->sizeBytes() + sizeof(bool);
}

LgsExpr* LgsNullable::getZeroValue() {
    assert(0);
}

Type* LgsNullable::getIRType(LgsCgModule& cg) {
    if (IRType) return IRType;
    if (passByRef) IRType = cg.ptrTy();
    IRType = cg.getStructType({baseType->getIRType(cg), cg.i1Ty()}, getName());
    return IRType;
}

Constant* LgsNullable::getRTType(LgsCgModule& cg) {
    const auto genericName = getGenericName();
    if (!baseType) {
        return cg.getRTTypeInfo(genericName, 0, 0, RTT_ANY, cg.null());
    }
    const auto st = cg.getStructType({cg.ptrTy(), cg.i1Ty()}, genericName);
    const auto baseRTType = baseType->getRTType(cg);
    const auto sv = ConstantStruct::get(st, {baseRTType, cg.i1(passByRef)});
    return cg.getRTTypeInfo(genericName, sizeBytes(), sizeBytes(), RTT_NULLABLE, sv);
}

bool LgsNullable::canCastTo(LgsType* other) {
    if (other->getName() == LgsAny::name) return true;
    const auto otherNullable = other->asNullable();
    if (!otherNullable) return false;
    if (!baseType) return true;
    return baseType->canCastTo(otherNullable->baseType);
}

Value* LgsNullable::addIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto leftNullable = left->type->asNullable();
    const auto rightNullable = right->type->asNullable();
    const auto result = cg.builder.CreateAlloca(getIRType(cg));
    if (passByRef) {
        const auto leftNotNull = cg.builder.CreateIsNotNull(left->IRValue);
        const auto rightNotNull = cg.builder.CreateIsNotNull(right->IRValue);
        const auto bothNotNull = cg.builder.CreateAnd(leftNotNull, rightNotNull);
        const auto addBlock = cg.createBlock();
        const auto nullBlock = cg.createBlock();
        const auto exitBlock = cg.createBlock();
        cg.builder.CreateCondBr(bothNotNull, addBlock, nullBlock);

        cg.startBlock(addBlock);
        const auto tempExpr1 = leftNullable->baseType->getZeroValue();
        const auto tempExpr2 = rightNullable->baseType->getZeroValue();
        const auto sum = baseType->addIR(cg, tempExpr1, tempExpr2);
        cg.builder.CreateStore(sum, result);
        cg.builder.CreateBr(exitBlock);

        cg.startBlock(nullBlock);
        cg.builder.CreateStore(cg.null(), result);
        cg.builder.CreateBr(exitBlock);

        cg.startBlock(exitBlock);
        freeExpr(tempExpr1);
        freeExpr(tempExpr2);
    } else {
        const auto isSet1 = leftNullable->getIsSet(cg, left->IRValue);
        const auto isSet2 = rightNullable->getIsSet(cg, right->IRValue);
        const auto bothSet = cg.builder.CreateAnd(isSet1, isSet2);

        const auto addBlock = cg.createBlock();
        const auto nullBlock = cg.createBlock();
        const auto exitBlock = cg.createBlock();
        cg.builder.CreateCondBr(bothSet, addBlock, nullBlock);

        cg.startBlock(addBlock);
        const auto tempExpr1 = leftNullable->baseType->getZeroValue();
        const auto tempExpr2 = rightNullable->baseType->getZeroValue();
        tempExpr1->IRValue = leftNullable->getNullableValue(cg, left->IRValue);
        tempExpr2->IRValue = rightNullable->getNullableValue(cg, right->IRValue);
        const auto sum = baseType->addIR(cg, tempExpr1, tempExpr2);
        setNullableFields(cg, result, sum, cg.true_());
        cg.builder.CreateBr(exitBlock);

        cg.startBlock(nullBlock);
        setIsSet(cg, result, cg.false_());
        cg.builder.CreateBr(exitBlock);

        cg.startBlock(exitBlock);
        freeExpr(tempExpr1);
        freeExpr(tempExpr2);
    }
    return result;
}

std::string LgsNullable::fmtStr() const {
    assert(0);
}

DIType* LgsNullable::getDebugType(LgsCgModule& cg) {
    assert(0);
}

LgsType* LgsNullable::applyBinOp(LgsType* toType, LgsBinOp& op) {
    const auto nullable = toType->asNullable();
    if (!nullable) return nullptr;
    switch (op.opType) {
    case NE:
    case EQ:
        if (!baseType || !nullable->baseType) return &LGS_BOOL;
        if (baseType->canCastTo(nullable->baseType)) return &LGS_BOOL;
        break;
    case ADD:
        if (!baseType) return toType;
        return new LgsNullable(baseType->applyBinOp(nullable->baseType, op));
    default:
        assert(0);
    }
    return nullptr;
}

std::string LgsNullable::getName() {
    return baseType ? baseType->getName() + name : LGS_NULL_LITERAL;
}

std::string LgsNullable::pname() {
    return baseType ? baseType->getName() + '?' : LGS_NULL_LITERAL;
}

Value* LgsNullable::getNullableValue(LgsCgModule& cg, Value* ptr) {
    const auto valueField = cg.builder.CreateStructGEP(getIRType(cg), ptr, 0);
    return cg.builder.CreateLoad(baseType->getIRType(cg), valueField);
}

Value* LgsNullable::getIsSet(LgsCgModule& cg, Value* ptr) {
    const auto isSetField = cg.builder.CreateStructGEP(getIRType(cg), ptr, 1);
    return cg.builder.CreateLoad(cg.i1Ty(), isSetField);
}

void LgsNullable::setNullableValue(LgsCgModule& cg, Value* ptr, Value* value) {
    const auto valueField = cg.builder.CreateStructGEP(getIRType(cg), ptr, 0);
    cg.builder.CreateStore(value, valueField);
}

void LgsNullable::setIsSet(LgsCgModule& cg, Value* ptr, Value* value) {
    const auto isSetField = cg.builder.CreateStructGEP(getIRType(cg), ptr, 1);
    cg.builder.CreateStore(value, isSetField);
}

void LgsNullable::setNullableFields(LgsCgModule& cg, Value* ptr, Value* value, Value* isSet) {
    const auto ty = getIRType(cg);
    const auto gepValue = cg.builder.CreateStructGEP(ty, ptr, 0);
    const auto gepIsSet = cg.builder.CreateStructGEP(ty, ptr, 1);
    cg.builder.CreateStore(value, gepValue);
    cg.builder.CreateStore(isSet, gepIsSet);
}