#include "exprs/LgsVariable.h"
#include "exprs/LgsInstance.h"
#include "exprs/LgsNull.h"
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
    case SUBTYPE:
        assert(0);
    case UNKNOWN:
        return nullptr;
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
    cg.builder.CreateStore(expr->IRValue, ref.varDec->IRValue);
}

Value* LgsVariable::hash(LgsLLVMGen& cg) {
    switch (ref.symbolType) {
    case PARAM:
        return cg.callLgsFunc("hash", cg.i32Ty(), {cg.ptrTy()}, {ref.param->IRValue});
    case VAR_DEC:
        return ref.varDec->expr->hash(cg);
    case FIELD:
        if (type->asEnum()) return cg.i32(hashStr(ref.field->name.c_str()));
        return cg.callLgsFunc("hash", cg.i32Ty(), {cg.ptrTy()}, {ref.field->IRValue});
    default:
        assert(0);
    }
}

std::string LgsVariable::asText() {
    return name;
}