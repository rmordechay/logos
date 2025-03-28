#include "exprs/unary/LgsArrayIndex.h"
#include "stmts/LgsVarDec.h"
#include <exprs/unary/LgsArray.h>

Value* LgsArrayIndex::createIRValue(CodeGenMetadata* metadata) {
    const auto symbol = metadata->logosStack.getSymbol(baseExpr->getName());
    switch (symbol->type) {
    case VAR_DEC: {
        if (const auto array = symbol->varDec->expr->asArray()) {
            const auto lastExprIRValue = lastExpr()->getIRValue(metadata);
            return array->getIRFuncGetElement(metadata, lastExprIRValue);
        }
        break;
    }
    default:
        break;
    }
    return nullptr;
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
    for (const auto &indexExpr : indexExprs) {
        delete indexExpr;
    }
}
