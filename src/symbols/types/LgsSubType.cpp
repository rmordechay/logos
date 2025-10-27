#include "types/LgsSubType.h"
#include "types/LgsAny.h"

Type* LgsSubType::getIRType(LgsLLVMGen& cg) {
    return subtype->getIRType(cg);
}

size_t LgsSubType::getSizeBytes() {
    return subtype->getSizeBytes();
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

Lgs_RTType LgsSubType::getRTType() {
    return subtype->getRTType();
}

std::string LgsSubType::strFormatPart() const {
    return subtype->strFormatPart();
}