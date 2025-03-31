#include "exprs/unary/LgsArrayIndex.h"

#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsVariable.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsArrayType.h"

#include <exprs/unary/LgsArray.h>

Value* LgsArrayIndex::createIRValue(CodeGenMetadata* metadata) {
    Value* IRValue = nullptr;
    const auto index = lastExpr()->getIRValue(metadata);
    if (const auto array = baseExpr->asArray()) {
        IRValue = array->getIRValue(metadata);
    } else if (const auto funcCall = baseExpr->asFuncCall()) {
        IRValue = funcCall->getIRValue(metadata);
    } else if (const auto var = baseExpr->asVariable()) {
        IRValue = var->getIRValue(metadata);
    } else {
        assert(false && "array index case not implemented");
    }
    const auto arrayType = dynamic_cast<LgsArrayType*>(baseExpr->type);
    return arrayType->getIRFuncGetElement(metadata, IRValue, index);
}

string LgsArrayIndex::getName() {
    return baseExpr->getName();
}

LgsExpr* LgsArrayIndex::lastExpr() const {
    if (indexExprs.empty()) return nullptr;
    return indexExprs[indexExprs.size() - 1];
}

LgsArrayIndex::~LgsArrayIndex() {
    delete baseExpr;
    for (const auto& indexExpr : indexExprs) {
        delete indexExpr;
    }
}
