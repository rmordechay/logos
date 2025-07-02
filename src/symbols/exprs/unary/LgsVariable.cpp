#include "exprs/unary/LgsVariable.h"
#include "exprs/unary/LgsEnumField.h"
#include "funcs/LgsFunc.h"
#include "funcs/LgsParam.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "utils/LgsUtils.h"
#include <logos/LgsModule.h>

string LgsVariable::getExprName() {
    return name;
}

string LgsVariable::prettyName() {
    return name;
}

Value* LgsVariable::createIRValue(LgsModule* module) {
    switch (ref.symbolType) {
    case VAR_DEC:
        return ref.varDec->IRValue;
    case PARAM:
        return ref.param->getIRValue(module);
    case FUNC:
        return ref.func->getIRFunc(module);
    case ENUM_FIELD:
        return getIRStr(module, ref.enumField->name);
    default:
        assert(0);
    }
}

bool LgsVariable::equals(LgsExpr* other) {
    if (const auto otherVar = other->asVariable()) {
        return ref.getSymbol() == otherVar->ref.getSymbol();
    }
    assert(0);
}

LgsExpr* LgsVariable::convertExpr(LgsType* type) {
    switch (ref.symbolType) {
    case VAR_DEC:
        return ref.varDec->expr->convertExpr(type);
    case FIELD:
        return ref.field->expr->convertExpr(type);
    case PARAM:
    case ENUM_FIELD:
    case FUNC:
    case OBJECT:
    case INTERFACE:
    case GROUP:
    case ENUM:
    case UNKNOWN:
        break;
    }
    assert(0);
}

Value* LgsVariable::hashValue(LgsModule* module) {
    string text;
    switch (ref.symbolType) {
    case PARAM:
        return module->builder.CreateCall(getStrHash(module), {ref.param->getIRValue(module)});
    case VAR_DEC:
        return ref.varDec->expr->hashValue(module);
    case FIELD:
        return ref.field->expr->hashValue(module);
    case ENUM_FIELD:
        return module->builder.getInt32(hashString(ref.enumField->name));
    default:
        assert(0);
    }
}