#include "types/LgsGenericType.h"
#include "types/LgsAny.h"

#include <cassert>

Type* LgsGenericType::getIRType(LgsCgModule& cg) {
    return nullptr;
}

Constant* LgsGenericType::getRTType(LgsCgModule& cg) {
    return nullptr;
}

LgsType* LgsGenericType::replaceGenerics(LgsType* replacement, std::unordered_map<std::string, LgsType*>& replacements) {
    replacements[name] = replacement;
    return replacement;
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

LgsType* LgsGenericType::clone() {
    const auto newGeneric = new LgsGenericType(*this);
    return newGeneric;
}

DIType* LgsGenericType::getDebugType(LgsCgModule& cg) {
    assert(0);
}
