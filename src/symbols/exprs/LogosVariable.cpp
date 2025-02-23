#include "exprs/LogosVariable.h"

#include "exprs/LogosFuncCall.h"
#include "exprs/LogosSelection.h"
#include "funcs/LogosFunc.h"
#include "object/LogosField.h"

#include <LogosStack.h>
#include <exprs/LogosArray.h>
#include <exprs/LogosArrayIndex.h>
#include <exprs/LogosBinaryExpr.h>
#include <exprs/LogosConstant.h>
#include <funcs/LogosFuncImpl.h>

Value* LogosVariable::computeIRValue(CodeGenMetadata* metadata) {
    const auto symbol = metadata->logosStack.getSymbol(name);
    switch (symbol->type) {
    case FIELD:
        return symbol->field->writeIRValue(metadata);
    case FUNC_CALL:
        return symbol->funcCall->writeIRValue(metadata);
    case SELECTION:
        return symbol->selection->writeIRValue(metadata);
    case BINARY_EXPR:
        return symbol->binaryExpr->writeIRValue(metadata);
    case INSTANCE:
        return symbol->instance->writeIRValue(metadata);
    case CONSTANT:
        return symbol->constant->writeIRValue(metadata);
    case FUNC_IMPL:
        return symbol->funcImpl->writeIRValue(metadata);
    case METHOD_IMPL:
        return symbol->methodImpl->writeIRValue(metadata);
    case ARRAY:
        return symbol->array->writeIRValue(metadata);
    case ARRAY_INDEX:
        return symbol->arrayIndex->writeIRValue(metadata);
    default:
        return nullptr;
    }
}

LogosSymbolType LogosVariable::getSymbolType() {
    return VARIABLE;
}

void LogosVariable::setName(const string name) {
    this->name = name;
}

string LogosVariable::getName() {
    return name;
}
