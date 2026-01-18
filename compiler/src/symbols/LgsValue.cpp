#include "LgsValue.h"

#include "LgsType.h"
#include "codegen/LgsCgModule.h"

Value* LgsValue::loadIR(LgsCgModule& cg) {
    assert(0);
}

void LgsValue::hashNode(size_t& oldHash) {
    assert(0);
}

LgsValue* LgsValue::clone() {
    assert(0);
}

std::string LgsValue::getName() {
    assert(0);
}

LgsType* LgsValue::getType() {
    assert(0);
}

Value* LgsValue::getLevel(LgsCgModule& cg) {
    const auto type = getType();
    assert(type->isHeapAlloc);
    return cg.load(cg.sizeTy(), cg.builder.CreateStructGEP(type->getIRType(cg), IRValue, 0));
}

void LgsValue::setDebugLoc(LgsCgModule& cg) const {
    cg.builder.SetCurrentDebugLocation(cg.getDebugLoc(location));
}
