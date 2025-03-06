#include "exprs/LogosArrayIndex.h"

#include "stmts/LogosVarDec.h"

#include <exprs/LogosArray.h>
#include <exprs/LogosConstant.h>
#include <llvm/IR/Module.h>

Value* LogosArrayIndex::computeIRValue(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    const auto irType = type->getIRType();
    const auto symbol = metadata->logosStack.getSymbol(baseExpr->getName());
    switch (symbol->type) {
    case VAR_DEC: {
        if (const auto array = dynamic_cast<LogosArray*>(symbol->varDec->expr)) {
            const auto arrPtr = array->writeIRValue(metadata);
            const auto lastExprIRValue = exprs[exprs.size() - 1]->writeIRValue(metadata);
            const auto lastElement = builder.CreateGEP(irType, arrPtr, lastExprIRValue);
            return builder.CreateLoad(irType, lastElement);;
        }
        break;
    }
    default:
        break;
    }
    return nullptr;
}

void LogosArrayIndex::setName(const string name) {
    baseExpr->setName(name);
}

string LogosArrayIndex::getName() {
    return baseExpr->getName();
}
