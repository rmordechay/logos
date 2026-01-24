#include "exprs/LgsNullableExpr.h"
#include "codegen/LgsCodeGen.h"

Value* LgsNullableExpr::loadIR(LgsCodeGen& cg) {
    if (isNull) return IRValue;
    return cg.load(type->getTypeOrPtr(cg), IRValue);
}

void LgsNullableExpr::assign(LgsCodeGen& cg, LgsExpr* right) {
    if (!type->passByRef) {
        const auto isSet = cg.builder.CreateIsNotNull(right->IRValue);
        type->asNullable()->setIRFields(cg, IRValue, right->IRValue, isSet);
        return;
    }
    cg.store(right->IRValue, IRValue);
}

void LgsNullableExpr::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}

void LgsNullableExpr::castImplicitly(LgsType* toType) {
    const auto otherNullable = toType->asNullable();
    if (isNull && otherNullable) {
        setType(otherNullable);
    }
}

std::string LgsNullableExpr::asText() {
    return baseExpr->asText() + '?';
}

LgsExpr* LgsNullableExpr::clone() {
    const auto newNullableExpr = new LgsNullableExpr(*this);
    if (newNullableExpr->baseExpr) {
        newNullableExpr->baseExpr = baseExpr->clone();
    }
    return newNullableExpr;
}
