#include "LgsValue.h"

#include "LgsType.h"
#include "codegen/LgsCodeGen.h"

LgsType* LgsValue::getType() {
    assert(0);
}

void LgsValue::setType(LgsType* newType) {
    assert(0);
}

void LgsValue::hashNode(size_t& oldHash) {
    assert(0);
}

LgsValue* LgsValue::clone() {
    assert(0);
}

void LgsValue::setDebugLoc(LgsCodeGen& cg) const {
    cg.builder.SetCurrentDebugLocation(cg.getDebugLoc(location));
}
