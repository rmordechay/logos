#include "stmts/LogosAssignment.h"

#include "LogosInstance.h"
#include "LogosSelection.h"
#include "LogosVariable.h"
#include "object/LogosField.h"

#include <LogosStack.h>
#include <types/LogosInt.h>

Value* LogosAssignment::computeIRValue(CodeGenMetadata* metadata) {
    // TODO make dynamic
    auto& builder = metadata->builder;
    if (const auto selection = dynamic_cast<LogosSelection*>(lvalue)) {
        const auto exprIRValue = rvalue->writeIRValue(metadata);
        const auto firstExprSymbol = metadata->logosStack.getSymbol(selection->firstExpr->getName());
        switch (firstExprSymbol->type) {
        case VAR_DEC:
            if (const auto instance = dynamic_cast<LogosInstance*>(firstExprSymbol->varDec->expr)) {
                const auto firstExprType = instance->type->getIRType();
                const auto firstExprValue = instance->writeIRValue(metadata);
                const auto field = instance->obj->getField(selection->innerExprs[0]->getName());
                const auto gep = builder.CreateStructGEP(firstExprType, firstExprValue, field->fieldPosition);
                builder.CreateStore(exprIRValue, gep);
            }
            break;
        default:
            break;;
        }
    }
    return nullptr;
}

LogosAssignment::~LogosAssignment() {
    delete lvalue;
    delete rvalue;
}
