#include "types/LgsGenericType.h"
#include "types/LgsAny.h"

#include <cassert>

Type* LgsGenericType::getIRType(LgsCodeGen& cg) {
    return nullptr;
}

Constant* LgsGenericType::getRTType(LgsCodeGen& cg) {
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

LgsType* LgsGenericType::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    assert(0);
}

std::string LgsGenericType::fmtStr() const {
    assert(0);
}

DIType* LgsGenericType::getDebugType(LgsCodeGen& cg) {
    assert(0);
}

bool LgsGenericType::canReplace(LgsType* type) {
    return true;
}
