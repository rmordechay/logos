#include "exprs/LgsVariable.h"
#include "exprs/LgsInstance.h"
#include "funcs/LgsParam.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include <codegen/LgsLLVMGen.h>

void LgsVariable::assign(LgsLLVMGen& cg, LgsExpr* expr) {
    IRValue = expr->loadIR(cg);
}

Value* LgsVariable::addIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto loadLeft = loadIR(cg);
    const auto loadRight = other->loadIR(cg);
    if (type->isInt) {
        return cg.builder.CreateAdd(loadLeft, loadRight);
    }
    return cg.builder.CreateFAdd(loadLeft, loadRight);
}

Value* LgsVariable::subIR(LgsLLVMGen& cg, LgsExpr* other) {
    switch (ref.symbolType) {
    case VAR_DEC:
        return ref.varDec->expr->subIR(cg, other);
    case PARAM:
        return ref.param->expr->subIR(cg, other);
    default:
        assert(0);
    }
}

Value* LgsVariable::mulIR(LgsLLVMGen& cg, LgsExpr* other) {
    switch (ref.symbolType) {
    case VAR_DEC:
        return ref.varDec->expr->mulIR(cg, other);
    case PARAM:
        return ref.param->expr->mulIR(cg, other);
    default:
        assert(0);
    }
}

Value* LgsVariable::divIR(LgsLLVMGen& cg, LgsExpr* other) {
    switch (ref.symbolType) {
    case VAR_DEC:
        return ref.varDec->expr->divIR(cg, other);
    case PARAM:
        return ref.param->expr->divIR(cg, other);
    default:
        assert(0);
    }
}

Value* LgsVariable::inIR(LgsLLVMGen& cg, LgsExpr* other) {
    assert(0);
}

Value* LgsVariable::modIR(LgsLLVMGen& cg, LgsExpr* other) {
    switch (ref.symbolType) {
    case VAR_DEC:
        return ref.varDec->expr->modIR(cg, other);
    default:
        assert(0);
    }
}

Value* LgsVariable::eqIR(LgsLLVMGen& cg, LgsExpr* other) {
    switch (ref.symbolType) {
    case VAR_DEC:
        return ref.varDec->expr->eqIR(cg, other);
    default:
        assert(0);
    }
}

Value* LgsVariable::neIR(LgsLLVMGen& cg, LgsExpr* other) {
    switch (ref.symbolType) {
    case VAR_DEC:
        return ref.varDec->expr->neIR(cg, other);
    default:
        assert(0);
    }
}

Value* LgsVariable::ltIR(LgsLLVMGen& cg, LgsExpr* other) {
    switch (ref.symbolType) {
    case VAR_DEC:
        return ref.varDec->expr->ltIR(cg, other);
    default:
        assert(0);
    }
}

Value* LgsVariable::gtIR(LgsLLVMGen& cg, LgsExpr* other) {
    switch (ref.symbolType) {
    case VAR_DEC:
        return ref.varDec->expr->gtIR(cg, other);
    default:
        assert(0);
    }
}

Value* LgsVariable::geIR(LgsLLVMGen& cg, LgsExpr* other) {
    switch (ref.symbolType) {
    case VAR_DEC:
        return ref.varDec->expr->geIR(cg, other);
    default:
        assert(0);
    }
}

Value* LgsVariable::leIR(LgsLLVMGen& cg, LgsExpr* other) {
    switch (ref.symbolType) {
    case VAR_DEC:
        return ref.varDec->expr->leIR(cg, other);
    default:
        assert(0);
    }
}

Value* LgsVariable::andIR(LgsLLVMGen& cg, LgsExpr* other) {
    assert(0);
}

Value* LgsVariable::orIR(LgsLLVMGen& cg, LgsExpr* other) {
    assert(0);
}

Value* LgsVariable::bitAndIR(LgsLLVMGen& cg, LgsExpr* other) {
    assert(0);
}

Value* LgsVariable::bitOrIR(LgsLLVMGen& cg, LgsExpr* other) {
    assert(0);
}

Value* LgsVariable::bitXorIR(LgsLLVMGen& cg, LgsExpr* other) {
    assert(0);
}

Value* LgsVariable::rshiftIR(LgsLLVMGen& cg, LgsExpr* other) {
    assert(0);
}

Value* LgsVariable::lshiftIR(LgsLLVMGen& cg, LgsExpr* other) {
    assert(0);
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
