#include "exprs/LogosVariable.h"

#include "exprs/LogosFuncCall.h"
#include "exprs/LogosSelection.h"
#include "funcs/LogosFunc.h"
#include "object/LogosField.h"
#include "object/LogosObject.h"

string LogosVariable::getName() {
    return name;
}

LogosSymbolType LogosVariable::getSymbolType() {
    return VARIABLE;
}

Value* LogosVariable::computeLLVMValue(CodeGenMetadata* metadata) {
    const auto symbol = metadata->theStack->getSymbol(name);
    switch (symbol->type) {
    case FIELD: {
        const auto expr = symbol->field->expr;
        if (expr) {
            return expr->getLLVMValue(metadata);
        }
        break;
    }
    case FUNC_CALL: {
        return symbol->funcCall->getLLVMValue(metadata);;
    }
    case SELECTION: {
        return symbol->selection->getLLVMValue(metadata);
    }
    default: break;
    }
    return nullptr;
}