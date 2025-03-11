#include "stmts/LogosField.h"
#include "LogosInstance.h"
#include "exprs/LogosExpr.h"
#include "types/LogosObject.h"

Value* LogosField::createIRValue(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    const auto IRType = type->getIRType();
    if (expr) {
        const auto value = expr->getIRValue(metadata);
        return builder.CreateGEP(IRType, value, nullptr);
    }
    const auto selfType = instance->obj->getIRType();
    const auto selfValue = instance->getIRValue(metadata);
    const auto gep = builder.CreateStructGEP(selfType, selfValue, fieldPosition);
    return builder.CreateLoad(IRType, gep);
}
