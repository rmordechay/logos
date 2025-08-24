#include "exprs/unary/LgsVariable.h"
#include "exprs/unary/LgsInstance.h"
#include "funcs/LgsFunc.h"
#include "funcs/LgsParam.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsTable.h"
#include <codegen/LgsLLVM.h>

Value* LgsVariable::hash(LgsLLVM& codeGen) {
    switch (ref.symbolType) {
    case PARAM:
        return codeGen.callHashStr(ref.param->IRValue);
    case VAR_DEC:
        return ref.varDec->expr->hash(codeGen);
    case ENUM_FIELD:
        return codeGen.i32(hashStr(ref.field->name.c_str()));
    default:
        assert(0);
    }
}

LgsExpr* LgsVariable::castTo(LgsType* toType) {
    switch (ref.symbolType) {
    case VAR_DEC:
        break;
    case PARAM:
        break;
    case ENUM_FIELD:
        break;
    case FUNC:
        break;
    case OBJECT:
        break;
    case INTERFACE:
        break;
    case GROUP:
        break;
    case ENUM:
        break;
    case TABLE:
        break;
    case UNKNOWN:
        break;
    }
    return this;
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
