#include "types/LgsSubType.h"
#include "types/LgsAny.h"

Type* LgsSubType::getIRType(LgsLLVMGen& cg) {
    return subtype->getIRType(cg);
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

Lgs_TypeKind LgsSubType::getRTTypeKind() {
    return subtype->getRTTypeKind();
}

std::string LgsSubType::strFormatPart() const {
    return subtype->strFormatPart();
}

LgsSubType* LgsSubType::clone() {
    assert(0);
}
