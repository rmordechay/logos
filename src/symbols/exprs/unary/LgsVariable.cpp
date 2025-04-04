#include "exprs/unary/LgsVariable.h"
#include "exprs/unary/LgsFuncCall.h"
#include "funcs/LgsParam.h"
#include <LgsStack.h>

string LgsVariable::getName() {
    return name;
}

Value* LgsVariable::createIRValue(CodeGenMetadata* metadata) {
    const auto symbol = metadata->logosStack.getSymbol(name);
    switch (symbol->type) {
    case VAR_DEC:
        return symbol->varDec->IRValue;
    case PARAM:
        return symbol->param->IRValue;
    default:
        return nullptr;
    }
}

Value* LgsVariable::eqIR(CodeGenMetadata* metadata, LgsExpr* other) {
    const auto symbol = metadata->logosStack.getSymbol(name);
    switch (symbol->type) {
    case VAR_DEC:
        return symbol->varDec->expr->eqIR(metadata, other);
    case PARAM:
    case OBJECT:
    case INTERFACE:
    case FUNC:
    case ENUM:
        break;
    }
    return nullptr;
}
