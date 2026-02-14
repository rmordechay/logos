#include "exprs/LgsNullableExpr.h"
#include "codegen/LgsCodeGen.h"

Value* LgsNullableExpr::loadIR(LgsCodeGen& cg) {
    if (isNull) return IRValue;
    return cg.load(type->getIRTypeOrPtr(cg), IRValue);
}

void LgsNullableExpr::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}

LgsExpr* LgsNullableExpr::cast(bool explicitly) {
    const auto otherNullable = implicitCast->asNullable();
    if (isNull && otherNullable) {
        type->asNullable()->baseType = otherNullable->baseType;
        type->passByRef = otherNullable->passByRef;
    }
    return this;
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
