#include "exprs/LogosVariable.h"

#include "exprs/LogosFuncCall.h"
#include "exprs/LogosSelection.h"
#include "funcs/LogosFunc.h"
#include "object/LogosField.h"

#include <exprs/LogosArray.h>
#include <exprs/LogosArrayIndex.h>
#include <exprs/LogosBinaryExpr.h>
#include <exprs/LogosConstant.h>

Value* LogosVariable::computeIRValue(CodeGenMetadata* metadata) {
    const auto symbol = metadata->theStack->getSymbol(name);
    switch (symbol->type) {
    case FIELD:
        return symbol->field->getIRValue(metadata);
    case FUNC_CALL:
        return symbol->funcCall->getIRValue(metadata);
    case SELECTION:
        return symbol->selection->getIRValue(metadata);
    case BINARY_EXPR:
        return symbol->binaryExpr->getIRValue(metadata);
    case INSTANCE:
        return symbol->instance->getIRValue(metadata);
    case VARIABLE:
        return symbol->variable->getIRValue(metadata);
    case CONSTANT:
        return symbol->constant->getIRValue(metadata);
    case FUNC:
        return symbol->func->getIRValue(metadata);
    case ARRAY:
        return symbol->array->getIRValue(metadata);
    case ARRAY_INDEX:
        return symbol->arrayIndex->getIRValue(metadata);
    default:
        return nullptr;
    }
}

LogosSymbolType LogosVariable::getSymbolType() {
    return VARIABLE;
}

string LogosVariable::getName() {
    return name;
}
