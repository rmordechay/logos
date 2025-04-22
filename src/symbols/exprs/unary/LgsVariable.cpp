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
    const auto symbol = metadata->lgsStack.getSymbol(name);
    assert(symbol);
    switch (symbol->type) {
    case VAR_DEC:
        return symbol->varDec->expr->getIRValue(metadata);
    case PARAM:
        return symbol->param->IRValue;
    case ENUM_FIELD:
        return symbol->enumField->getGEP(metadata);
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
    return tree;
}

uint32_t LgsVariable::hashValue(CodeGenMetadata* metadata) {
    const auto symbol = metadata->lgsStack.getSymbol(name);
    string text;
    switch (symbol->type) {
    case FIELD:
        return symbol->field->expr->hashValue(metadata);
    case ENUM_FIELD:
        return LgsStr::hashString(symbol->enumField->name);
    default:
        assert(false);
    }
}
