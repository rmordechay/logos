#include "types/LgsIterable.h"
#include "utils/LgsUtils.h"
#include "exprs/LgsExpr.h"
#include "exprs/unary/LgsIterIndex.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsAny.h"
#include "types/LgsArray.h"

Type* LgsIterable::getIRType() {
    if (IRType) return IRType;
    if (!isStatic || !sizeExpr) return PointerType::getUnqual(context);
    const auto innerIRType = baseType->getIRType();
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

Value* LgsIterable::getElement(LgsRuntime* runtime, Value* iterPtr, Value* iPtr) {
    assert(false);
}