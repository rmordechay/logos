#include "types/LgsGroup.h"



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

json::value LgsGroup::asJSON() {
    assert(0);
}

std::string LgsGroup::pname() {
    return name;
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
