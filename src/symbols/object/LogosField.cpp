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
        return builder.CreateGEP(type, value, nullptr);
    }
    const auto thisSymbol = metadata->logosStack.getSymbol("this");
    const auto objType = thisSymbol->object->getIRType();

    return builder.CreateStructGEP(objType, objPtr, fieldPosition);
}
