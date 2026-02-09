#include "types/LgsSelf.h"

#include <cassert>

#include "LgsDefinitions.h"

Type* LgsSelf::getIRType(LgsCodeGen& cg) {
    return baseType->getIRType(cg);
}

size_t LgsSelf::sizeBytes() {
    assert(0);
}

LgsExpr* LgsSelf::getZeroValue() {
    return baseType->getZeroValue();
}

std::string LgsSelf::getName() {
    return LGS_SELF_CLASS;
}

bool LgsSelf::canCastTo(LgsType* other) {
    return baseType && baseType->canCastTo(other);
}

LgsType* LgsSelf::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    return nullptr;
}

std::string LgsSelf::fmtStr() const {
    assert(0);
}

DIType* LgsSelf::getDebugType(LgsCodeGen& cg) {
    assert(0);
}