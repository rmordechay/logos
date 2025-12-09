#include "types/LgsSelf.h"

#include <cassert>

Type* LgsSelf::getIRType(LgsCgModule& cg) {
    assert(0);
}

Constant* LgsSelf::getRTType(LgsCgModule& cg) {
    assert(0);
}

size_t LgsSelf::sizeBytes() {
    assert(0);
}

LgsExpr* LgsSelf::getZeroValue() {
    return baseType->getZeroValue();
}

std::string LgsSelf::getName() {
    return name;
}

bool LgsSelf::canCastTo(LgsType* other) {
    assert(0);
}

LgsType* LgsSelf::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    assert(0);
}

std::string LgsSelf::fmtStr() const {
    assert(0);
}

DIType* LgsSelf::getDebugType(LgsCgModule& cg) {
    assert(0);
}