#include "types/LgsTypePair.h"

#include "utils/LgsUtils.h"

Type* LgsTypePair::getIRType(LgsLLVMGen& cg) {
    assert(0);
}

Lgs_rttype LgsTypePair::getRTType() {
    assert(0);
}

LgsExpr* LgsTypePair::getZeroValue() {
    assert(false);
}

size_t LgsTypePair::getSizeBytes() {
    return key->getSizeBytes() + value->getSizeBytes() ;
}

std::string LgsTypePair::getName() {
    return name;
}

std::string LgsTypePair::pname() {
    return '<' + key->pname() + ", " + value->pname() + '>';
}

bool LgsTypePair::canCastTo(LgsType* other) {
    const auto otherPair = dynamic_cast<LgsTypePair*>(other);
    if (!otherPair) return false;
    return key->canCastTo(otherPair->key) && value->canCastTo(otherPair->value);
}

std::string LgsTypePair::strFormatPart() const {
    return "%s";
}

LgsType* LgsTypePair::clone() {
    return new LgsTypePair(key->clone(), value->clone());
}

LgsTypePair::~LgsTypePair() {
    freeType(key);
    freeType(value);
}
