#include "exprs/unary/LgsVariable.h"
#include "exprs/unary/LgsEnumField.h"
#include "funcs/LgsFunc.h"
#include "funcs/LgsParam.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "utils/LgsUtils.h"
#include <logos/LgsRuntime.h>

string LgsVariable::getExprName() {
    return name;
}

string LgsVariable::prettyName() {
    return name;
}

Value* LgsVariable::createIRValue(LgsRuntime* runtime) {
    switch (ref.symbolType) {
    case VAR_DEC:
        return ref.varDec->IRValue;
    case PARAM:
        return ref.param->getIRValue(runtime);
    case FUNC:
        return ref.func->getIRFunc(runtime);
    case ENUM_FIELD:
        return getIRStr(runtime, ref.enumField->name);
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

uint32_t LgsVariable::hashValue(LgsRuntime* runtime) {
    string text;
    switch (ref.symbolType) {
    case FIELD:
        return ref.field->expr->hashValue(runtime);
    case ENUM_FIELD:
        return hashString(ref.enumField->name);
    default:
        assert(0);
    }
}