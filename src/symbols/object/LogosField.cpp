#include "object/LogosField.h"

#include "exprs/LogosExpr.h"
#include "object/LogosObject.h"

#include <LogosDefinitions.h>
#include <LogosStack.h>
#include <llvm/IR/Module.h>

Value* LogosField::computeIRValue(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    const auto type = inferredType->getIRType();
    if (expr) {
        const auto value = expr->writeIRValue(metadata);
        return builder.CreateGEP(type, value, nullptr);
    }
    const auto thisType = metadata->logosStack.getSymbol(LOGOS_THIS)->object->getIRType();
    const auto thisValue = metadata->logosStack.currentFunc->getArg(0);
    const auto gep = builder.CreateStructGEP(thisType, thisValue, fieldPosition);
    return builder.CreateLoad(type, gep);
}
