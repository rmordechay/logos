#include "types/LgsTypePair.h"

#include "LgsUtils.h"

#include <cassert>

Type* LgsTypePair::getIRType(LgsCgModule& cg) {
    assert(0);
}

Constant* LgsTypePair::getRTType(LgsCgModule& cg) {
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

std::string LgsTypePair::fmtStr() const {
    return "%s";
}

LgsType* LgsTypePair::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    assert(0);
}

DIType* LgsTypePair::getDebugType(LgsCgModule& cg) {
    assert(0);
}

LgsTypePair::~LgsTypePair() {
    freeType(key);
    freeType(value);
}
