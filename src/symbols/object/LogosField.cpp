#include "object/LogosField.h"

#include "exprs/LogosExpr.h"
#include "object/LogosObject.h"

#include <LogosStack.h>
#include <llvm/IR/Module.h>

Value* LogosField::computeIRValue(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    if (expr) {
        const auto type = inferredType->getIRType();
        const auto value = expr->writeIRValue(metadata);
        const auto gep = builder.CreateStructGEP(type, value, 0);
        return gep;
    }
    const auto gep = builder.CreateAlloca(inferredType->getIRType());
    const auto val = builder.getInt32(0);
    builder.CreateStore(val, gep);
    return val;
}

