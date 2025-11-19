#include "types/LgsUnknown.h"

std::string LgsUnknown::getName() {
    return name;
}

std::string LgsUnknown::pname() {
    return name;
}

LgsExpr* LgsUnknown::getZeroValue() {
    assert(0);
}

Lgs_TypeKind LgsUnknown::getRTTypeKind() {
    return RTT_UNKNOWN;
}

size_t LgsUnknown::sizeBytes() {
    return 0;
}

bool LgsUnknown::canCastTo(LgsType* other) {
    return false;
}

std::string LgsUnknown::strFormatPart() const {
    assert(0);
}

Type* LgsUnknown::getIRType(LgsLLVMGen& cg) {
    assert(0);
}
