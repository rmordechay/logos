#include "types/LgsIterable.h"
#include "exprs/LgsExpr.h"
#include "exprs/unary/LgsVariable.h"
#include "exprs/unary/constants/LgsIntConst.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsAny.h"

Type* LgsIterable::getIRType() {
    if (IRType) return IRType;
    if (!isConst || dimsExprs.empty()) return ptrTy;
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

Value* LgsIterable::IRLength(CodeGenMetadata* metadata) {
    assert(false);
}

void LgsIterable::unpackTypes(const vector<LgsVarDec*>& varDecs) {
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

int LgsIterable::getExprConstNumber(LgsExpr* expr) {
    if (const auto asInt = expr->asIntConst()) {
        return asInt->value;
    }
    if (const auto var = expr->asVariable()) {
        switch (var->ref->type) {
        case VAR_DEC:
            return getExprConstNumber(var->ref->varDec->expr);
        case FIELD:
            return getExprConstNumber(var->ref->field->expr);
        default:
            break;
        }
    }
    return -1;
}
