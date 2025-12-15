#include "exprs/LgsNullableExpr.h"
#include "codegen/LgsCgModule.h"

Value* LgsNullableExpr::loadIR(LgsCgModule& cg) {
    if (type->passByRef) return IRValue;
    return cg.builder.CreateLoad(type->getIRType(cg), IRValue);
}

void LgsNullableExpr::assign(LgsCgModule& cg, LgsExpr* expr) {
    if (type->isHeapAlloc) cg.freeValue(cg.builder.CreateLoad(cg.ptrTy(), IRValue), type->getRTType(cg));
    if (!type->passByRef) {
        const auto isSet = cg.builder.CreateIsNotNull(expr->IRValue);
        type->asNullable()->setNullableFields(cg, IRValue, expr->IRValue, isSet);
        return;
    }
    cg.builder.CreateStore(expr->IRValue, IRValue);
}

void LgsNullableExpr::setDebugValue(LgsCgModule& cg) {
    assert(0);
}

void LgsNullableExpr::castImplicitly(LgsType* toType) {
    const auto otherNullable = toType->asNullable();
    if (isNull && otherNullable) {
        type = otherNullable;
    }
}

std::string LgsNullableExpr::asText() {
    return baseExpr->asText() + '?';
}
