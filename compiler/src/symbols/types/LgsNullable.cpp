#include "types/LgsNullable.h"

#include "LgsBinaryTokens.h"
#include "LgsDefinitions.h"
#include "codegen/LgsCgModule.h"
#include "exprs/LgsExpr.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsBool.h"
#include <cassert>

LgsField* LgsNullable::getField(const std::string& fieldName) {
    return baseType->getField(fieldName);
}

size_t LgsNullable::sizeBytes() {
    if (passByRef) return sizeof(void*);
    return baseType->sizeBytes() + sizeof(bool);
}

LgsExpr* LgsNullable::getZeroValue() {
    assert(0);
}

std::string LgsNullable::pname() {
    return baseType ? baseType->getName() + '?' : LGS_NULL_LITERAL;
}

std::string LgsNullable::getName() {
    return baseType ? baseType->getName() + name : LGS_NULL_LITERAL;
}

Type* LgsNullable::getIRType(LgsCgModule& cg) {
    if (IRType) return IRType;
    if (passByRef) IRType = cg.ptrTy();
    else IRType = cg.getStructType({baseType->getIRType(cg), cg.i1Ty()}, getName());
    return IRType;
}

Constant* LgsNullable::getRTType(LgsCgModule& cg) {
    const auto nullableName = getName();
    if (!baseType) return cg.getRTTypeInfo(name, 0, RTT_ANY, isHeapAlloc, cg.null());
    const auto sv = cg.getRTTExtraStruct(nullableName, {cg.ptrTy(), cg.i1Ty()}, {baseType->getRTType(cg), cg.i1(passByRef)});
    return cg.getRTTypeInfo(nullableName, sizeBytes(), RTT_NULLABLE, isHeapAlloc, sv);
}

bool LgsNullable::canCastTo(LgsType* other) {
    if (other->getName() == LgsAny::name) return true;
    const auto otherNullable = other->asNullable();
    if (!otherNullable) return false;
    if (!baseType) return true;
    return baseType->canCastTo(otherNullable->baseType);
}

std::string LgsNullable::fmtStr() const {
    assert(0);
}

DIType* LgsNullable::getDebugType(LgsCgModule& cg) {
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

Value* LgsNullable::addIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto f = [this, &cg](LgsExpr* l, LgsExpr* r) {
        return baseType->addIR(cg, l, r);
    };
    return passByRef ? applyPtrBinOp(cg, left, right, f) : applyNumberBinOp(cg, left, right, f);
}

void LgsNullable::setNullableFields(LgsCgModule& cg, Value* ptr, Value* value, Value* isSet) {
    const auto ty = getIRType(cg);
    cg.setStructField(ty, ptr, 0, value);
    cg.setStructField(ty, ptr, 1, isSet);
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
    cg.setStructField(getIRType(cg), ptr, 0, value);
}

void LgsNullable::setIsSet(LgsCgModule& cg, Value* ptr, Value* value) {
    cg.setStructField(getIRType(cg), ptr, 1, value);
}

Value* LgsNullable::applyNumberBinOp(LgsCgModule& cg, const LgsExpr* left, const LgsExpr* right, const std::function<Value*(LgsExpr*, LgsExpr*)>& func) {
    const auto ptr = cg.builder.CreateAlloca(getIRType(cg));
    const auto leftNullable = left->type->asNullable();
    const auto rightNullable = right->type->asNullable();
    const auto addBlock = cg.createBlock();
    const auto nullBlock = cg.createBlock();
    const auto exitBlock = cg.createBlock();

    const auto isSet1 = leftNullable->getIsSet(cg, left->IRValue);
    const auto isSet2 = rightNullable->getIsSet(cg, right->IRValue);
    const auto bothSet = cg.builder.CreateAnd(isSet1, isSet2);
    cg.builder.CreateCondBr(bothSet, addBlock, nullBlock);

    cg.startBlock(addBlock);
    const auto tempExpr1 = leftNullable->baseType->getZeroValue();
    const auto tempExpr2 = rightNullable->baseType->getZeroValue();
    tempExpr1->IRValue = leftNullable->getNullableValue(cg, left->IRValue);
    tempExpr2->IRValue = rightNullable->getNullableValue(cg, right->IRValue);
    const auto result = func(tempExpr1, tempExpr2);
    setNullableFields(cg, ptr, result, cg.true_());
    cg.builder.CreateBr(exitBlock);

    cg.startBlock(nullBlock);
    setIsSet(cg, ptr, cg.false_());
    cg.builder.CreateBr(exitBlock);

    cg.startBlock(exitBlock);
    freeExpr(tempExpr1);
    freeExpr(tempExpr2);
    return ptr;
}

Value* LgsNullable::applyPtrBinOp(LgsCgModule& cg, const LgsExpr* left, const LgsExpr* right, const std::function<Value*(LgsExpr*, LgsExpr*)>& func) {
    const auto ptr = cg.builder.CreateAlloca(getIRType(cg));
    const auto leftNullable = left->type->asNullable();
    const auto rightNullable = right->type->asNullable();
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
    const auto result = func(tempExpr1, tempExpr2);
    cg.builder.CreateStore(result, ptr);
    cg.builder.CreateBr(exitBlock);

    cg.startBlock(nullBlock);
    cg.builder.CreateStore(cg.null(), ptr);
    cg.builder.CreateBr(exitBlock);

    cg.startBlock(exitBlock);
    freeExpr(tempExpr1);
    freeExpr(tempExpr2);
    return ptr;
}
