#include "exprs/LgsNullableExpr.h"
#include "codegen/LgsCgModule.h"

Value* LgsNullableExpr::loadIR(LgsCgModule& cg) {
    if (type->passByRef) return IRValue;
    return cg.builder.CreateLoad(type->getIRType(cg), IRValue);
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
    assert(0);
}
