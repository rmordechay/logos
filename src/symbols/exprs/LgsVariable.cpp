#include "exprs/LgsVariable.h"
#include "exprs/LgsInstance.h"
#include "exprs/LgsNull.h"
#include "funcs/LgsParam.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "utils/LgsUtils.h"
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
    case FUNC:
        return IRValue;
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
        return cg.callLgsFunc("hash", cg.sizeTy(), {cg.ptrTy()}, {ref.param->IRValue});
    case VAR_DEC:
        return ref.varDec->expr->hash(cg);
    case FIELD:
        if (ref.field->isEnumField) return cg.usize(ref.field->position);
        if (ref.field->type->asEnum()) return cg.builder.CreateLoad(cg.sizeTy(), ref.field->getGEP(cg));
        return cg.callLgsFunc("hash", cg.sizeTy(), {cg.ptrTy()}, {ref.field->IRValue});
    default:
        assert(0);
    }
}

std::string LgsVariable::asText() {
    return name;
}

LgsExpr* LgsVariable::cloneExpr() {
    const auto newVariable = new LgsVariable(*this);
    newVariable->ref = ref.clone();
    if (type) newVariable->type = type->clone();
    return newVariable;
}
