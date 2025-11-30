#include "types/LgsUnknown.h"

#include <cassert>

std::string LgsUnknown::getName() {
    return name;
}

std::string LgsUnknown::pname() {
    return name;
}

LgsExpr* LgsUnknown::getZeroValue() {
    assert(0);
}

size_t LgsUnknown::sizeBytes() {
    return 0;
}

bool LgsUnknown::canCastTo(LgsType* other) {
    return false;
}

LgsType* LgsUnknown::applyBinOp(LgsType* toType, LgsBinOp& op) {
    assert(0);
}

std::string LgsUnknown::strFormatPart() const {
    assert(0);
}

DIType* LgsUnknown::getDebugType(LgsCgModule& cg) {
    assert(0);
}

Type* LgsUnknown::getIRType(LgsCgModule& cg) {
    assert(0);
}

Constant* LgsUnknown::getRTType(LgsCgModule& cg) {
    assert(0);
}
