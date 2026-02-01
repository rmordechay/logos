#include "stmts/LgsField.h"
#include "LgsType.h"
#include "exprs/LgsExpr.h"
#include "exprs/LgsHashMap.h"

void LgsField::setType(LgsType* newType) {
    type = newType;
}

Value* LgsField::loadIR(LgsCodeGen& cg) {
    if (type->asEnum()) return IRValue;
    return cg.load(type->getIRType(cg), IRValue);
}

std::string LgsField::getName() {
    return name;
}

LgsType* LgsField::getType() {
    return type;
}

Value* LgsField::getGEP(LgsCodeGen& cg, Value* parentIRPtr) {
    if (gep) return gep;
    assert(parentType && parentIRPtr);
    const auto ty = parentType->getIRType(cg);
    if (parentType->asVec()) {
        gep = cg.builder.CreateGEP(ty, parentIRPtr, {cg.zero32(), cg.i32(position)});
    } else {
        gep = cg.builder.CreateStructGEP(ty, parentIRPtr, position);
    }
    return gep;
}

void LgsField::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}

LgsField::~LgsField() {
    freeExpr(expr);
    freeType(type);
    expr = nullptr;
    type = nullptr;
}
