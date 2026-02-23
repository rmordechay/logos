#include "types/LgsSubType.h"

#include <cassert>

Type* LgsSubType::getIRType(LgsCodeGen& cg) {
    return subtype->getIRType(cg);
}

Constant* LgsSubType::getRTTypeExtra(LgsCodeGen& cg) {
    return subtype->getRTType(cg);
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
    if (other->isAny()) return true;
    return getName() == otherName;
}

LgsType* LgsSubType::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    return nullptr;
}

std::string LgsSubType::fmtStr() const {
    return subtype->fmtStr();
}

DIType* LgsSubType::getDebugType(LgsCodeGen& cg) {
    assert(0);
}