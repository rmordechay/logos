#include "unary/LogosArrayIndex.h"
#include "stmts/LogosVarDec.h"
#include <unary/LogosArray.h>
#include <unary/constants/LogosConstant.h>

Value* LogosArrayIndex::computeIRValue(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    const auto irType = type->getIRType();
    const auto symbol = metadata->logosStack.getSymbol(baseExpr->getName());
    switch (symbol->type) {
    case VAR_DEC: {
        if (const auto array = dynamic_cast<LogosArray*>(symbol->varDec->expr)) {
            const auto arrPtr = array->writeIRValue(metadata);
            const auto lastExprIRValue = indexExprs[indexExprs.size() - 1]->writeIRValue(metadata);
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

string LogosArrayIndex::getName() {
    return baseExpr->getName();
}

LogosArrayIndex::~LogosArrayIndex() {
    delete baseExpr;
    for (const auto &indexExpr : indexExprs) {
        delete indexExpr;
    }
}
