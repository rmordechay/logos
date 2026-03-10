#include "types/LgsTypeParam.h"

#include <cassert>

Type* LgsTypeParam::getIRType(LgsCodeGen& cg) {
    assert(0);
}

size_t LgsTypeParam::sizeBytes() {
    assert(0);
}

LgsExpr* LgsTypeParam::getZeroValue() {
    assert(0);
}

std::string LgsTypeParam::getName() {
    return name;
}

bool LgsTypeParam::canCastTo(LgsType* other) {
    if (!bounds) return true;
    return other->canCastTo(bounds);
}

LgsType* LgsTypeParam::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    return nullptr;
}

std::string LgsTypeParam::fmtStr() const {
    assert(0);
}

DIType* LgsTypeParam::getDebugType(LgsCodeGen& cg) {
    assert(0);
}

LgsTypeParam* LgsTypeParam::clone() {
    const auto cloned = new LgsTypeParam(*this);
    if (bounds) cloned->bounds = bounds->clone();
    return cloned;
}

LgsTypeParam::~LgsTypeParam() {
    freeType(bounds);
    bounds = nullptr;
}
