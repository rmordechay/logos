#include "types/LgsNullable.h"

#include <llvm/ADT/ArrayRef.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Instructions.h>
#include <llvm/Support/Casting.h>
#include <cassert>
#include <vector>

#include "LgsBinaryTokens.h"
#include "codegen/LgsCodeGen.h"
#include "exprs/LgsExpr.h"
#include "exprs/LgsNullableExpr.h"
#include "types/primitives/LgsBool.h"
#include "LgsRTTIndices.h"
#include "exprs/LgsBinaryExpr.h"
#include "LgsDefinitions.h"

namespace llvm {
class Value;
}

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

std::string LgsNullable::pname() {
    return baseType ? baseType->pname() + '?' : name;
}

std::string LgsNullable::getName() {
    return baseType ? baseType->getName() + name : name;
}

std::string LgsNullable::fmtStr() const {
    assert(0);
}

LgsExpr* LgsNullable::getZeroValue() {
    return new LgsNullableExpr();
}

bool LgsNullable::canCastTo(LgsType* other) {
    if (isNull || other->isAny()) return true;
    const auto otherNullable = other->asNullable();
    if (!otherNullable) return false;
    return baseType->canCastTo(otherNullable->baseType);
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

Type* LgsNullable::getIRType(LgsCodeGen& cg) {
    if (passByRef) return cg.ptrTy();
    return cg.getStructType({baseType->getIRType(cg), cg.i1Ty()}, getName());
}

Constant* LgsNullable::getRTTypeExtra(LgsCodeGen& cg) {
    return baseType->asObject() ? cg.null() : baseType->getRTType(cg);
}

void LgsNullable::asIRText(LgsStrBuilder& sb, Value* value) {
    if (!baseType || isa<ConstantPointerNull>(value)) {
        sb.add(LGS_NULL_LITERAL);
        return;
    }
    auto& cg = sb.cg;
    if (passByRef) {
        cg.ifElseStmt(
            cg.isNull(value),
            [&](BasicBlock*){sb.add(LGS_NULL_LITERAL);},
            [&](BasicBlock*){baseType->asIRText(sb, value);}
        );
    } else {
        cg.ifElseStmt(
            loadIsSet(cg, value),
            [&](BasicBlock*){baseType->asIRText(sb, loadValue(cg, value));},
            [&](BasicBlock*){sb.add(LGS_NULL_LITERAL);}
        );
    }
}

Value* LgsNullable::getIRZeroValue(LgsCodeGen& cg, Value* pointee, Value* level) {
    if (passByRef) {
        if (pointee) cg.store(cg.null(), pointee);
        return cg.null();
    }
    const auto ty = getIRType(cg);
    const auto ptr = pointee ? pointee : cg.builder.CreateAlloca(ty);
    cg.storeField(ty, ptr, LgsNullableExprIndices::isSet, cg.false_());
    return ptr;
}

Value* LgsNullable::moveValue(LgsCodeGen& cg, Value* value, Value* toLevel) {
    return cg.moveValue(baseType->getBaseName(), value, toLevel);
}

Value* LgsNullable::addIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    const auto f = [this, &cg](LgsBinaryExpr* e) {return baseType->addIR(cg, e);};
    return passByRef ? applyPtrBinOp(cg, binExpr, f) : applyNumberBinOp(cg, binExpr, f);
}

Value* LgsNullable::hashValue(LgsCodeGen& cg, Value* value) {
    if (passByRef) {
        const auto phi = cg.builder.CreatePHI(cg.sizeTy(), 2);
        auto ifTrue = [&](BasicBlock* block) {phi->addIncoming(cg.zeroSize(), block);};
        auto ifFalse = [&](BasicBlock* block) {phi->addIncoming(baseType->hashValue(cg, value), block);};
        cg.ifElseStmt(cg.isNull(value), ifTrue, ifFalse);
        return phi;
    } else {

    }
    assert(0);
}

void LgsNullable::setIRFields(LgsCodeGen& cg, Value* ptr, Value* value, Value* isSet) {
    const auto ty = getIRType(cg);
    cg.storeField(ty, ptr, LgsNullableExprIndices::value, value);
    cg.storeField(ty, ptr, LgsNullableExprIndices::isSet, isSet);
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
    cg.storeField(ty, ptr, LgsNullableExprIndices::isSet, cg.false_());
    cg.builder.CreateBr(exitBlock);

    cg.startBlock(exitBlock);
    return ptr;
}

DIType* LgsNullable::getDebugType(LgsCodeGen& cg) {
    assert(0);
}

Value* LgsNullable::loadValue(LgsCodeGen& cg, Value* ptr) {
    return cg.builder.CreateExtractValue(ptr, LgsNullableExprIndices::value);
}

Value* LgsNullable::loadIsSet(LgsCodeGen& cg, Value* ptr) {
    return cg.builder.CreateExtractValue(ptr, LgsNullableExprIndices::isSet);
}
