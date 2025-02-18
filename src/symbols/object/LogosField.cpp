#include "object/LogosField.h"

#include "exprs/LogosExpr.h"
#include "object/LogosObject.h"

#include <LogosStack.h>
#include <llvm/IR/Module.h>

Value* LogosField::computeIRValue(CodeGenMetadata* metadata) {
    if (expr) {
        const auto type = inferredType->getIRType();
        const auto value = expr->writeIRValue(metadata);
        return metadata->builder->CreateStructGEP(type, value, fieldPosition);
    }
    metadata->logosStack->addGlobalSymbol(name, LogosSymbol(FIELD, this));
    return nullptr;
}
