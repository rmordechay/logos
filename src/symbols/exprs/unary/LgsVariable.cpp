#include "exprs/unary/LgsVariable.h"

#include "exprs/unary/LgsInstance.h"
#include "funcs/LgsFunc.h"
#include "funcs/LgsParam.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsObject.h"

#include "utils/LgsUtils.h"
#include <logos/LgsCodeGen.h>

extern "C" {
    size_t Str_hash(const char* key);
}

string LgsVariable::prettyName() {
    return name;
}

Value* LgsVariable::createIRValue(LgsCodeGen* codeGen) {
    switch (ref.symbolType) {
    case VAR_DEC:
        return ref.varDec->IRValue;
    case PARAM:
        return ref.param->getIRValue(codeGen);
    case FUNC:
        return ref.func->getIRFunc(codeGen);
    case OBJECT:
        return ref.object->singleton->getIRValue(codeGen);
    case ENUM:
        return codeGen->getIRStr(name);
    case FIELD:
        return nullptr;
    case INTERFACE:
    case GROUP:
    case UNKNOWN:
        break;
    }
    assert(0);
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

Value* LgsVariable::hashValue(LgsCodeGen* codeGen) {
    switch (ref.symbolType) {
    case PARAM:
        return codeGen->callStrHash(ref.param->getIRValue(codeGen));
    case VAR_DEC:
        return ref.varDec->expr->hashValue(codeGen);
    case FIELD:
        return codeGen->i32(Str_hash(ref.field->name.c_str()));
    default:
        assert(0);
    }
}
