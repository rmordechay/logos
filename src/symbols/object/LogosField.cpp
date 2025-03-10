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
    const auto symbol = metadata->logosStack.getSymbol(LOGOS_SELF);
    const auto selfType = symbol->param->type->getIRType();
    const auto selfValue = metadata->logosStack.currentFunc->getArg(0);
    const auto gep = builder.CreateStructGEP(selfType, selfValue, fieldPosition);
    return builder.CreateLoad(IRType, gep);
}
