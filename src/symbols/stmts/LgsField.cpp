#include "stmts/LgsField.h"
#include "LgsType.h"
#include "exprs/LgsExpr.h"
#include "exprs/LgsHashMap.h"
#include "utils/LgsUtils.h"

void LgsField::setType(LgsType* newType) {
    type = newType;
}

Value* LgsField::loadIR(LgsLLVMGen& cg) {
    if (!IRValue) {
        IRValue = getGEP(cg);
    }
    return cg.builder.CreateLoad(type->getIRType(cg), IRValue);
}

Value* LgsField::getGEP(LgsLLVMGen& cg) const {
    assert(parentIRValue);
    return cg.builder.CreateStructGEP(parent->getIRType(cg), parentIRValue, position);
}

Value* LgsField::resolveVirtualField(LgsLLVMGen* cg, const LgsHashMap* vtable) const {
    const auto vtableMap = vtable->type->asMap();
    const auto fieldIRType = type->getIRType(*cg);
    const auto keyIR = cg->getIRStr(name);
    const auto vtableIRType = vtable->type->getIRType(*cg);
    const auto mapPtr = cg->builder.CreateGEP(vtableIRType, parentIRValue, {cg->i64Zero()});
    const auto rv = vtableMap->getIRElement(*cg, mapPtr, keyIR);
    return cg->builder.CreateLoad(fieldIRType, rv);
}

LgsField::~LgsField() {
    freeExpr(expr);
    freeType(type);
    expr = nullptr;
    setType(nullptr);
}

LgsField* LgsField::clone() {
    assert(0);
}
