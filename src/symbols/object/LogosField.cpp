#include "object/LogosField.h"

#include "LogosExpr.h"
#include "object/LogosObject.h"

#include <LogosDefinitions.h>
#include <LogosStack.h>

Value* LogosField::computeIRValue(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    const auto IRType = type->getIRType();
    if (expr) {
        const auto value = expr->writeIRValue(metadata);
        return builder.CreateGEP(IRType, value, nullptr);
    }
    const auto thisType = metadata->logosStack.getSymbol(LOGOS_THIS)->object->getIRType();
    const auto thisValue = metadata->logosStack.currentFunc->getArg(0);
    const auto gep = builder.CreateStructGEP(thisType, thisValue, fieldPosition);
    return builder.CreateLoad(IRType, gep);
}
