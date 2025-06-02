#include "types/LgsIterable.h"
#include "utils/LgsUtils.h"
#include "exprs/LgsExpr.h"
#include "exprs/unary/LgsIterIndex.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsAny.h"
#include "types/LgsArray.h"

Type* LgsIterable::getIRType() {
    if (IRType) return IRType;
    if (!isStatic || !sizeExpr) return ptrTy;
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

Value* LgsIterable::getElement(Module* module, Value* iterPtr, Value* iPtr) {
    assert(false);
}

Value* LgsIterable::getLength(Module* module, Value* iterValue) {
    assert(false);
}

LgsType* LgsIterable::getIterType(const LgsIndex* index) const {
    if (index->to) {
        const auto sliced = new LgsArray(baseType->clone());
        sliced->isStatic = isStatic;
        return sliced;
    }
    return baseType;
}
