#include "types/LgsIterable.h"
#include "exprs/LgsExpr.h"
#include "stmts/LgsVarDec.h"

Type* LgsIterable::getIRType(LgsRuntime* runtime) {
    if (IRType) return IRType;
    if (!isStatic || !sizeExpr) return runtime->builder.getPtrTy();
    const auto innerIRType = baseType->getIRType(runtime);
    const auto size = LgsExpr::getExprConstNumber(sizeExpr);
    IRType = ArrayType::get(innerIRType, size);
    return IRType;
}

LgsType* LgsIterable::getBaseType() {
    return baseType;
}

void LgsIterable::unpackTypes(const vector<LgsVarDec*>& varDecs) {
    varDecs[0]->type = baseType;
}
