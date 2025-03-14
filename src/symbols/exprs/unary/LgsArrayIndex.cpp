#include "unary/LgsArrayIndex.h"
#include "stmts/LgsVarDec.h"
#include <unary/LgsArray.h>
#include <unary/constants/LgsConst.h>

Value* LgsArrayIndex::createIRValue(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    const auto irType = type->getIRType();
    const auto symbol = metadata->logosStack.getSymbol(baseExpr->getName());
    switch (symbol->type) {
    case VAR_DEC: {
        if (const auto array = dynamic_cast<LgsArray*>(symbol->varDec->expr)) {
            const auto arrPtr = array->getIRValue(metadata);
            const auto lastExprIRValue = indexExprs[indexExprs.size() - 1]->getIRValue(metadata);
            const auto lastElement = builder.CreateGEP(irType, arrPtr, lastExprIRValue);
            return builder.CreateLoad(irType, lastElement);
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

LgsArrayIndex::~LgsArrayIndex() {
    delete baseExpr;
    for (const auto &indexExpr : indexExprs) {
        delete indexExpr;
    }
}
