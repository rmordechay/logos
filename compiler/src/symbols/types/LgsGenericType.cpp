#include "types/LgsGenericType.h"
#include "types/LgsAny.h"

#include <cassert>

Type* LgsGenericType::getIRType(LgsCgModule& cg) {
    return nullptr;
}

Constant* LgsGenericType::getRTType(LgsCgModule& cg) {
    return nullptr;
}

size_t LgsGenericType::sizeBytes() {
    assert(0);
}

LgsExpr* LgsGenericType::getZeroValue() {
    assert(0);
}

std::string LgsGenericType::getName() {
    return name;
}

bool LgsGenericType::canCastTo(LgsType* other) {
    return true;
}

LgsType* LgsGenericType::applyBinOp(LgsType* toType, LgsBinOp& op) {
    assert(0);
}

std::string LgsGenericType::fmtStr() const {
    assert(0);
}

DIType* LgsGenericType::getDebugType(LgsCgModule& cg) {
    assert(0);
}
