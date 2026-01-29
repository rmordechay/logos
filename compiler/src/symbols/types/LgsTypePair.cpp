#include "types/LgsTypePair.h"

#include "LgsUtils.h"

#include <cassert>

#include "codegen/LgsCodeGen.h"

Type* LgsTypePair::getIRType(LgsCodeGen& cg) {
    return cg.getStructType({key->getIRType(cg), value->getIRType(cg), cg.ptrTy()}, name);
}

Constant* LgsTypePair::getRTType(LgsCodeGen& cg) {
    assert(0);
}

LgsExpr* LgsTypePair::getZeroValue() {
    assert(false);
}

size_t LgsTypePair::sizeBytes() {
    return key->sizeBytes() + value->sizeBytes() + sizeof(void*);
}

std::string LgsTypePair::getName() {
    return name + key->getName() + value->getName();
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

DIType* LgsTypePair::getDebugType(LgsCodeGen& cg) {
    assert(0);
}

LgsTypePair::~LgsTypePair() {
    freeType(key);
    freeType(value);
}
