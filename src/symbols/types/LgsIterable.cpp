#include "types/LgsIterable.h"
#include "utils/LgsUtils.h"
#include "exprs/LgsExpr.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsAny.h"

Type* LgsIterable::getIRType() {
    if (IRType) return IRType;
    if (!isStatic || dimsExprs.empty()) return ptrTy;
    IRType = baseType->getIRType();
    for (int i = dimsExprs.size() - 1; i >= 0; i--) {
        IRType = ArrayType::get(IRType, getExprConstNumber(dimsExprs[i]));
    }
    return IRType;
}

LgsType* LgsIterable::getBaseType() {
    return baseType;
}

int LgsIterable::getDims() {
    assert(false);
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

LgsType* LgsIterable::inferTypeFromIter(const vector<LgsExpr*>& exprs) const {
    if (exprs.empty()) return nullptr;
    const auto type = exprs[0]->type;
    for (int i = 0; i < exprs.size(); ++i) {
        const auto exprType = exprs[i]->type;
        if (!type->equals(exprType)) {
            return &LGS_ANY;
        }
    }
    return type;
}
