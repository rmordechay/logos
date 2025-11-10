#include "types/LgsGeneric.h"
#include "types/LgsAny.h"

Type* LgsGeneric::getIRType(LgsLLVMGen& cg) {
    assert(0);
}

size_t LgsGeneric::getSizeBytes() {
    assert(0);
}

LgsExpr* LgsGeneric::getZeroValue() {
    assert(0);
}

Lgs_TypeKind LgsGeneric::getRTTypeKind() {
    return RTT_STR;
}

std::string LgsGeneric::getName() {
    return name;
}

bool LgsGeneric::canCastTo(LgsType* other) {
    return true;
}

LgsGeneric* LgsGeneric::clone() {
    return new LgsGeneric(*this);
}

std::string LgsGeneric::strFormatPart() const {
    assert(0);
}
