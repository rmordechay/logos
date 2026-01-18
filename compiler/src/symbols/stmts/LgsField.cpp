#include "stmts/LgsField.h"
#include "LgsType.h"
#include "exprs/LgsExpr.h"
#include "exprs/LgsHashMap.h"

void LgsField::setType(LgsType* newType) {
    type = newType;
}

Value* LgsField::loadIR(LgsCgModule& cg) {
    return cg.load(type->getIRType(cg), IRValue);
}

std::string LgsField::getName() {
    return name;
}

LgsType* LgsField::getType() {
    return type;
}

Value* LgsField::getGEP(LgsCgModule& cg, Value* parentIRPtr) const {
    assert(parentType && parentIRPtr);
    return cg.builder.CreateStructGEP(parentType->getIRType(cg), parentIRPtr, position);
}

void LgsField::setDebugValue(LgsCgModule& cg) {
    assert(0);
}

LgsField::~LgsField() {
    freeExpr(expr);
    freeType(type);
    expr = nullptr;
    type = nullptr;
}
