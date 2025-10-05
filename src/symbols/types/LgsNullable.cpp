#include "types/LgsNullable.h"
#include "codegen/LgsLLVMGen.h"
#include "exprs/LgsNull.h"
#include "utils/LgsUtils.h"

Type* LgsNullable::getIRType(LgsLLVMGen& cg) {
    return cg.getStructType({cg.ptrTy(), cg.i1Ty()});
}

LgsExpr* LgsNullable::getZeroValue() {
    return new LgsNull();
}

Lgs_RTType LgsNullable::getRTType() {
    assert(0);
}

std::string LgsNullable::getName() {
    return baseType->getName() + "?";
}

std::string LgsNullable::pname() {
    return baseType->pname() + '?';
}

json::value LgsNullable::asJsonStr() {
    assert(0);
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
