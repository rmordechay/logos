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

LgsType* LgsUnknown::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    return nullptr;
}

std::string LgsUnknown::fmtStr() const {
    assert(0);
}

DIType* LgsUnknown::getDebugType(LgsCodeGen& cg) {
    assert(0);
}

Type* LgsUnknown::getIRType(LgsCodeGen& cg) {
    assert(0);
}

LgsType* LgsUnknown::clone() {
    return new LgsUnknown(*this);
}