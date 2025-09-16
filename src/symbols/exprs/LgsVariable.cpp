#include "exprs/LgsVariable.h"
#include "exprs/LgsInstance.h"
#include "funcs/LgsParam.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include <codegen/LgsLLVMGen.h>

void LgsVariable::assign(LgsLLVMGen& cg, LgsExpr* expr) {
    if (owner) freeOwner(cg);
    IRValue = expr->IRValue;
}

Value* LgsVariable::loadIR(LgsLLVMGen& cg) {
    switch (ref.symbolType) {
    case PARAM:
        return ref.param->loadIR(cg);
    case VAR_DEC:
        return ref.varDec->loadIR(cg);
    case FIELD:
        return ref.field->loadIR(cg);
    default:
        assert(0);
    }
}

Value* LgsVariable::hash(LgsLLVMGen& cg) {
    switch (ref.symbolType) {
    case PARAM:
        return cg.callHashStr(ref.param->IRValue);
    case VAR_DEC:
        return ref.varDec->expr->hash(cg);
    case FIELD:
        return cg.i32(hashStr(ref.field->name.c_str()));
    default:
        assert(0);
    }
}

LgsExpr* LgsVariable::castTo(LgsType* toType) {
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
