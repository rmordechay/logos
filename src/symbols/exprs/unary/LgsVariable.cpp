#include "exprs/unary/LgsVariable.h"
#include "exprs/unary/LgsEnumField.h"
#include "funcs/LgsParam.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsStr.h"
#include <LgsStack.h>

string LgsVariable::getName() {
    return name;
}

Value* LgsVariable::createIRValue(CodeGenMetadata* metadata) {
    assert(ref && ref->type != UNKNOWN);
    switch (ref->type) {
    case VAR_DEC:
        return ref->varDec->expr->getIRValue(metadata);
    case PARAM:
        return ref->param->IRValue;
    case ENUM_FIELD:
        return ref->enumField->getGEP(metadata);
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

json LgsVariable::asJSON() {
    json tree;
    tree["name"] = name;
    tree["exprType"] = "VARIABLE";
    tree["type"] = type->getName();
    tree["ref"] = ref->asJSON();
    return tree;
}

uint32_t LgsVariable::hashValue() {
    assert(ref && ref->type != UNKNOWN);
    string text;
    switch (ref->type) {
    case FIELD:
        return ref->field->expr->hashValue();
    case ENUM_FIELD:
        return LgsStr::hashString(ref->enumField->name);
    default:
        assert(false);
    }
}

LgsVariable::~LgsVariable() {
    delete ref;
}