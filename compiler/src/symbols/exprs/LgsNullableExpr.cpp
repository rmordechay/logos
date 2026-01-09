#include "exprs/LgsNullableExpr.h"
#include "codegen/LgsCgModule.h"

Value* LgsNullableExpr::loadIR(LgsCgModule& cg) {
    if (isNull) return IRValue;
    return cg.load(type->getTypeOrPtr(cg), IRValue);
}

void LgsNullableExpr::assign(LgsCgModule& cg, LgsExpr* expr) {
    if (type->isHeapAlloc) {
        cg.freeValue(loadIR(cg));
    }
    if (!type->passByRef) {
        const auto isSet = cg.builder.CreateIsNotNull(expr->IRValue);
        type->asNullable()->setNullableFields(cg, IRValue, expr->IRValue, isSet);
        return;
    }
    cg.store(expr->IRValue, IRValue);
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
