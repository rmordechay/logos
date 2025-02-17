#include "exprs/LogosVariable.h"

#include "exprs/LogosFuncCall.h"
#include "exprs/LogosSelection.h"
#include "funcs/LogosFunc.h"
#include "object/LogosField.h"
#include "object/LogosObject.h"

Value* LogosVariable::computeIRValue(CodeGenMetadata* metadata) {
    const auto symbol = metadata->theStack->getSymbol(name);
    switch (symbol->type) {
    case FIELD: {
        const auto field = symbol->field;
        break;
    }
    case FUNC_CALL: {
        return symbol->funcCall->getIRValue(metadata);
    }
    case SELECTION: {
        return symbol->selection->getIRValue(metadata);
    }
    default: break;
    }
    return nullptr;
}

LogosSymbolType LogosVariable::getSymbolType() {
    return VARIABLE;
}

string LogosVariable::getName() {
    return name;
}
