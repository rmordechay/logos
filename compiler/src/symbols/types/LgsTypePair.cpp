#include "types/LgsTypePair.h"

#include "LgsUtils.h"

#include <cassert>

llvm::Type* LgsTypePair::getIRType(LgsCgModule& cg) {
    assert(0);
}

llvm::Constant* LgsTypePair::getRTType(LgsCgModule& cg) {
    assert(0);
}

LgsExpr* LgsTypePair::getZeroValue() {
    assert(false);
}

size_t LgsTypePair::sizeBytes() {
    return key->sizeBytes() + value->sizeBytes() ;
}

std::string LgsTypePair::getName() {
    return name + key->pname() + value->pname();
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

llvm::DIType* LgsTypePair::getDebugType(LgsCgModule& cg) {
    assert(0);
}

LgsTypePair::~LgsTypePair() {
    freeType(key);
    freeType(value);
}
