#include "exprs/unary/LgsVariable.h"

#include "exprs/unary/LgsEnumField.h"
#include "exprs/unary/LgsFuncCall.h"
#include "funcs/LgsParam.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsEnum.h"

#include <LgsStack.h>

string LgsVariable::getName() {
    return name;
}

Value* LgsVariable::createIRValue(CodeGenMetadata* metadata) {
    assert(ref.type != UNKNOWN);
    switch (ref.type) {
    case VAR_DEC:
        return ref.varDec->expr->getIRValue(metadata);
    case PARAM:
        return ref.param->IRValue;
    case ENUM_FIELD:
        return ref.enumField->getIRValue(metadata);
    default:
        assert(false);
    }
}

Value* LgsVariable::eqIR(CodeGenMetadata* metadata, LgsExpr* other) {
    const auto symbol = metadata->lgsStack.getSymbol(name);
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
    case UNKNOWN:
        assert(false);
    }
    return nullptr;
}
