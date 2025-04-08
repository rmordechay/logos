#include "exprs/unary/LgsVariable.h"

#include "exprs/unary/LgsEnumField.h"
#include "exprs/unary/LgsFuncCall.h"
#include "funcs/LgsParam.h"
#include "types/LgsEnum.h"

#include <LgsStack.h>

string LgsVariable::getName() {
    return name;
}

Value* LgsVariable::createIRValue(CodeGenMetadata* metadata) {
    const auto symbol = metadata->logosStack.getSymbol(name);
    switch (symbol->type) {
    case VAR_DEC:
        return symbol->varDec->expr->getIRValue(metadata);
    case PARAM:
        return symbol->param->IRValue;
    case ENUM_FIELD:
        return symbol->enumField->getIRValue(metadata);
    default:
        assert(false);
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
    case ENUM_FIELD:
        break;
    }
    return nullptr;
}
