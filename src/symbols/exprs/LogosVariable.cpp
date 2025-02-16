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

Value* LogosVariable::getLLVMValue(CodeGenMetadata* metadata) {
    const auto symbol = metadata->theStack->getSymbol(name);
    switch (symbol->type) {
    case FIELD: {
        const auto expr = symbol->field->expr;
        if (expr) {
            llvmValue = expr->getLLVMValue(metadata);
            return llvmValue;
        }
        break;
    }
    case FUNC_CALL: {
        llvmValue = symbol->funcCall->getLLVMValue(metadata);
        return llvmValue;
    }
    case SELECTION: {
        return symbol->selection->getLLVMValue(metadata);
    }
    default: break;
    }
    return nullptr;
}