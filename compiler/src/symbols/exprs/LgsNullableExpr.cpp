#include "exprs/LgsNullableExpr.h"
#include "codegen/LgsCodeGen.h"

void LgsNullableExpr::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}

LgsExpr* LgsNullableExpr::cast(LgsType* toType, const bool explicitly) {
    const auto otherNullable = toType->asNullable();
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
