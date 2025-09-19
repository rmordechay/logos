#include "types/LgsNullable.h"
#include "codegen/LgsLLVMGen.h"
#include "utils/LgsUtils.h"

Type* LgsNullable::getIRType(LgsLLVMGen& cg) {
    return cg.ptrTy();
}

std::string LgsNullable::getName() {
    return baseType->getName() + "?";
}

LgsExpr* LgsNullable::getZeroValue() {
    return baseType->getZeroValue();
}

json::value LgsNullable::asJSON() {
    assert(0);
}

std::string LgsNullable::pname() {
    return baseType->pname() + '?';
}

bool LgsNullable::canCastTo(LgsType* other) {
    return baseType->canCastTo(other);
}

size_t LgsNullable::getSizeBytes() {
    return 0;
}

std::string LgsNullable::strFormatPart() const {
    return baseType->strFormatPart();
}

LgsNullable::~LgsNullable() {
    if (baseType) {
        freeType(baseType);
        baseType = nullptr;
    }
}
