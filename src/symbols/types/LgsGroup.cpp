#include "types/LgsGroup.h"

LgsFunc* LgsGroup::getMethod(const std::string& methodName) {
    const auto method = targetMethods.find(methodName);
    if (method != targetMethods.end() && method->second) {
        return method->second;
    }
    return nullptr;
}

Type* LgsGroup::getIRType(LgsLLVMGen& cg) {
    return cg.ptrTy();
}

LgsExpr* LgsGroup::getZeroValue() {
    assert(0);
}

Lgs_RTType LgsGroup::getRTType() {
    assert(0);
}

std::string LgsGroup::getName() {
    return name;
}

json::value LgsGroup::asJsonStr() {
    assert(0);
}

size_t LgsGroup::getSizeBytes() {
    assert(0);
}

std::string LgsGroup::strFormatPart() const {
    return "%s";
}

bool LgsGroup::canCastTo(LgsType* other) {
    for (const auto type : types) {
        if (type->canCastTo(other)) return true;
    }
    return false;
}
