#include "types/LgsGenericType.h"
#include "types/LgsAny.h"

#include <cassert>

Type* LgsGenericType::getIRType(LgsCodeGen& cg) {
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
    if (!bounds) return true;
    return other->canCastTo(bounds);
}

LgsType* LgsGenericType::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    return nullptr;
}

std::string LgsGenericType::fmtStr() const {
    assert(0);
}

LgsType* LgsGenericType::replaceGenerics(std::unordered_map<std::string, LgsType*>& replacements) {
    const auto r = replacements.find(name);
    return r != replacements.end() && r->second ? r->second : nullptr;
}

DIType* LgsGenericType::getDebugType(LgsCodeGen& cg) {
    assert(0);
}
