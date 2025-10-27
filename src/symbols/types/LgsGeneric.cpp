#include "types/LgsGeneric.h"

Type* LgsGeneric::getIRType(LgsLLVMGen& cg) {
    assert(0);
}

size_t LgsGeneric::getSizeBytes() {
    assert(0);
}

LgsExpr* LgsGeneric::getZeroValue() {
    assert(0);
}

Lgs_RTType LgsGeneric::getRTType() {
    assert(0);
}

std::string LgsGeneric::getName() {
    assert(0);
}

bool LgsGeneric::canCastTo(LgsType* other) {
    assert(0);
}

std::string LgsGeneric::strFormatPart() const {
    assert(0);
}
