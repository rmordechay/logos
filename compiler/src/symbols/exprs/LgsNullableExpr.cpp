#include "exprs/LgsNullableExpr.h"
#include "codegen/LgsCgModule.h"

Value* LgsNullableExpr::loadIR(LgsCgModule& cg) {
    if (isNull) return IRValue;
    return cg.load(type->getTypeOrPtr(cg), IRValue);
}

void LgsNullableExpr::assign(LgsCgModule& cg, LgsExpr* right) {
    if (!type->passByRef) {
        const auto isSet = cg.builder.CreateIsNotNull(right->IRValue);
        type->asNullable()->setNullableFields(cg, IRValue, right->IRValue, isSet);
        return;
    }
    cg.store(right->IRValue, IRValue);
}

void LgsNullableExpr::setDebugValue(LgsCgModule& cg) {
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
