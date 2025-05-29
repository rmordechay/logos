#include "types/LgsIterable.h"
#include "utils/LgsUtils.h"
#include "exprs/LgsExpr.h"
#include "exprs/unary/LgsIterIndex.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsAny.h"
#include "types/array/LgsArray.h"

Type* LgsIterable::getIRType() {
    if (IRType) return IRType;
    if (!isStatic || !dimsExpr) return ptrTy;
    const auto innerIRType = baseType->getIRType();
    const auto size = getExprConstNumber(dimsExpr);
    IRType = ArrayType::get(innerIRType, size);
    return IRType;
}

LgsType* LgsIterable::getBaseType() {
    return baseType;
}

void LgsIterable::unpackTypes(const vector<LgsVarDec*>& varDecs) {
    varDecs[0]->type = baseType;
}

Value* LgsIterable::getElement(CodeGenMetadata* metadata, Value* iterPtr, Value* iPtr) {
    assert(false);
}

Value* LgsIterable::getLength(CodeGenMetadata* metadata, Value* iterValue) {
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
