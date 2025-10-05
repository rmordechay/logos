#include "exprs/LgsVariable.h"
#include "exprs/LgsInstance.h"
#include "funcs/LgsParam.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include <codegen/LgsLLVMGen.h>

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

bool LgsVariable::equals(LgsExpr* other) {
    const auto otherVar = other->asVariable();
    if (!otherVar) return false;
    switch (ref.symbolType) {
    case VAR_DEC:
        return ref.varDec->name == otherVar->name;
    default:
        break;
    }
    assert(0);
}

LgsExpr* LgsVariable::castTo(LgsType* toType, const bool explicitCast) {
    switch (ref.symbolType) {
    case PARAM:
        assert(0);
    case VAR_DEC:
        return ref.varDec->expr->castTo(toType);
    case FIELD:
        assert(0);
    default:
        assert(0);
    }
}

Value* LgsVariable::castToIR(LgsLLVMGen& cg, LgsType* toType) {
    switch (ref.symbolType) {
    case PARAM:
        assert(0);
    case VAR_DEC:
        return ref.varDec->expr->castToIR(cg, toType);
    case FIELD:
        assert(0);
    default:
        assert(0);
    }
}

void LgsVariable::assign(LgsLLVMGen& cg, LgsExpr* expr) {
    freeOwner(cg);
    owner = expr->owner;
    IRValue = expr->IRValue;
}

Value* LgsVariable::addIR(LgsLLVMGen& cg, Value* other) {
    switch (ref.symbolType) {
    case PARAM:
        return ref.param->addIR(cg, other);
    case VAR_DEC:
        return ref.varDec->expr->addIR(cg, other);
    case FIELD:
        return ref.field->addIR(cg, other);
    default:
        assert(0);
    }
}

Value* LgsVariable::subIR(LgsLLVMGen& cg, Value* other) {
        switch (ref.symbolType) {
    case PARAM:
        return ref.param->subIR(cg, other);
    case VAR_DEC:
        return ref.varDec->expr->subIR(cg, other);
    case FIELD:
        return ref.field->subIR(cg, other);
    default:
        assert(0);
    }
}

Value* LgsVariable::mulIR(LgsLLVMGen& cg, Value* other) {
        switch (ref.symbolType) {
    case PARAM:
        return ref.param->mulIR(cg, other);
    case VAR_DEC:
        return ref.varDec->expr->mulIR(cg, other);
    case FIELD:
        return ref.field->mulIR(cg, other);
    default:
        assert(0);
    }
}

Value* LgsVariable::divIR(LgsLLVMGen& cg, Value* other) {
        switch (ref.symbolType) {
    case PARAM:
        return ref.param->divIR(cg, other);
    case VAR_DEC:
        return ref.varDec->expr->divIR(cg, other);
    case FIELD:
        return ref.field->divIR(cg, other);
    default:
        assert(0);
    }
}

Value* LgsVariable::eqIR(LgsLLVMGen& cg, Value* other) {
    assert(0);
}

Value* LgsVariable::neIR(LgsLLVMGen& cg, Value* other) {
    assert(0);
}

Value* LgsVariable::ltIR(LgsLLVMGen& cg, Value* other) {
    assert(0);
}

Value* LgsVariable::gtIR(LgsLLVMGen& cg, Value* other) {
    assert(0);
}

Value* LgsVariable::geIR(LgsLLVMGen& cg, Value* other) {
    assert(0);
}

Value* LgsVariable::leIR(LgsLLVMGen& cg, Value* other) {
    assert(0);
}

Value* LgsVariable::andIR(LgsLLVMGen& cg, Value* other) {
    assert(0);
}

Value* LgsVariable::orIR(LgsLLVMGen& cg, Value* other) {
    assert(0);
}

Value* LgsVariable::hash(LgsLLVMGen& cg) {
    switch (ref.symbolType) {
    case PARAM:
        return cg.callLgsFunc("hash", cg.i32Ty(), {cg.ptrTy()}, {ref.param->IRValue});
    case VAR_DEC:
        return ref.varDec->expr->hash(cg);
    case FIELD:
        return cg.i32(hashStr(ref.field->name.c_str()));
    default:
        assert(0);
    }
}

std::string LgsVariable::getName() {
    return name;
}

json::value LgsVariable::asJsonStr() {
    json::object jsonObj;
    jsonObj["exprType"] = "variable";
    jsonObj["name"] = name;
    jsonObj["type"] = type->asJsonStr();
    return jsonObj;
}
