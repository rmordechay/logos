#include "types/LgsIterable.h"
#include "exprs/LgsExpr.h"
#include "logos/LgsRuntime.h"
#include "stmts/LgsVarDec.h"

Type* LgsIterable::getIRType() {
    if (IRType) return IRType;
    if (!isStatic || !sizeExpr) return PointerType::getUnqual(context);
    const auto innerIRType = baseType->getIRType();
    const auto size = getExprConstNumber(sizeExpr);
    IRType = ArrayType::get(innerIRType, size);
    return IRType;
}

LgsType* LgsIterable::getBaseType() {
    return baseType;
}

void LgsIterable::unpackTypes(const vector<LgsVarDec*>& varDecs) {
    varDecs[0]->type = baseType;
}
