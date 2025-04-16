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

uint32_t LgsVariable::hashValue() {
    assert(ref && ref->type != UNKNOWN);
    switch (ref->type) {
    case FIELD:
        break;
    default:
        assert(false);
    }
    return 0;
}

Value* LgsVariable::createIRValue(CodeGenMetadata* metadata) {
    assert(ref && ref->type != UNKNOWN);
    switch (ref->type) {
    case VAR_DEC:
        return ref->varDec->expr->getIRValue(metadata);
    case PARAM:
        return ref->param->IRValue;
    case ENUM_FIELD:
        return ref->enumField->getIRValue(metadata);
    default:
        assert(false);
    }
}

Value* LgsVariable::eqIR(CodeGenMetadata* metadata, LgsExpr* other) {
    const auto symbol = metadata->lgsStack.getSymbol(name);
    switch (symbol->type) {
    case VAR_DEC:
        return symbol->varDec->expr->eqIR(metadata, other);
    case UNKNOWN:
        assert(false);
    default:
        break;
    }
    return nullptr;
}

LgsVariable::~LgsVariable() {
    delete ref;
}
