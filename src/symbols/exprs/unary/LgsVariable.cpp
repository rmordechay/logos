#include "exprs/unary/LgsVariable.h"
#include "exprs/unary/LgsInstance.h"
#include "funcs/LgsFunc.h"
#include "funcs/LgsParam.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsObject.h"
#include <logos/LgsCodeGen.h>

void LgsVariable::createIRValue(LgsCodeGen* codeGen) {
    switch (ref.symbolType) {
    case VAR_DEC:
        IRValue = ref.varDec->getIRValue(codeGen);
        return;
    case PARAM:
        IRValue = ref.param->getIRValue(codeGen);
        return;
    case FUNC:
        IRValue = ref.func->getIRFunc(codeGen);
        return;
    case OBJECT:
        assert(ref.object->singleton);
        IRValue = ref.object->singleton->getIRValue(codeGen);
        return;
    case ENUM:
    case ENUM_FIELD:
        IRValue = codeGen->getIRStr(name);
        return;
    case INTERFACE:
    case GROUP:
    case UNKNOWN:
        break;
    }
    assert(0);
}

Value* LgsVariable::hash(LgsCodeGen* codeGen) {
    switch (ref.symbolType) {
    case PARAM:
        return codeGen->callHashStr(ref.param->getIRValue(codeGen));
    case VAR_DEC:
        return ref.varDec->expr->hash(codeGen);
    case ENUM_FIELD:
        return codeGen->i32(hashStr(ref.field->name.c_str()));
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

std::string LgsVariable::pname() {
    return name;
}

json::value LgsVariable::asJSON() {
    json::object jsonObj;
    jsonObj["exprType"] = "variable";
    jsonObj["name"] = name;
    jsonObj["type"] = type->asJSON();
    return jsonObj;
}
