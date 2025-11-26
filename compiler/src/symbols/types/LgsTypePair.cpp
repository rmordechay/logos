#include "types/LgsTypePair.h"

#include "LgsUtils.h"

Type* LgsTypePair::getIRType(LgsLLVMGen& cg) {
    assert(0);
}

Constant* LgsTypePair::getRTType(LgsLLVMGen& cg) {
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

llvm::DIType* LgsTypePair::getDebugType(LgsLLVMGen& cg) {
    assert(0);
}

LgsType* LgsTypePair::clone() {
    return new LgsTypePair(key->clone(), value->clone());
}

LgsTypePair::~LgsTypePair() {
    freeType(key);
    freeType(value);
}
