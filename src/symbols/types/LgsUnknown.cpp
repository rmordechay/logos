#include "types/LgsUnknown.h"

json::value LgsUnknown::asJsonStr() {
    assert(0);
}

std::string LgsUnknown::getName() {
    return name;
}

LgsExpr* LgsUnknown::getZeroValue() {
    assert(0);
}

Lgs_RTType LgsUnknown::getRTType() {
    return RTT_UNKNOWN;
}

size_t LgsUnknown::getSizeBytes() {
    return 0;
}

bool LgsUnknown::canCastTo(LgsType* other) {
    return false;
}

std::string LgsUnknown::strFormatPart() const {
    assert(0);
}

llvm::Type* LgsUnknown::getIRType(LgsLLVMGen& cg) {
    assert(0);
}
