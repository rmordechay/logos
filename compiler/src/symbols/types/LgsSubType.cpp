#include "types/LgsSubType.h"
#include "types/LgsAny.h"

#include <cassert>

Type* LgsSubType::getIRType(LgsCgModule& cg) {
    return subtype->getIRType(cg);
}

Constant* LgsSubType::getRTType(LgsCgModule& cg) {
    assert(0);
}

size_t LgsSubType::sizeBytes() {
    return subtype->sizeBytes();
}

LgsExpr* LgsSubType::getZeroValue() {
    return subtype->getZeroValue();
}

std::string LgsSubType::getName() {
    if (isWeakType) return subtype->getName();
    return name;
}

std::string LgsSubType::pname() {
    return name;
}

bool LgsSubType::canCastTo(LgsType* other) {
    const auto otherName = other->getName();
    if (otherName == LgsAny::name) return true;
    return getName() == otherName;
}

LgsType* LgsSubType::applyBinOp(LgsType* toType, LgsBinOp& op) {
    assert(0);
}

std::string LgsSubType::fmtStr() const {
    return subtype->fmtStr();
}

DIType* LgsSubType::getDebugType(LgsCgModule& cg) {
    assert(0);
}