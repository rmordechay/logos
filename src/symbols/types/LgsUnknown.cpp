#include "types/LgsUnknown.h"

json::value LgsUnknown::asJSON() {
    assert(0);
}

std::string LgsUnknown::pname() {
    return getName();
}

std::string LgsUnknown::getName() {
    return name;
}

LgsExpr* LgsUnknown::getZeroValue() {
    assert(0);
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

llvm::Type* LgsUnknown::getIRType(LgsLLVM& codeGen) {
    assert(0);
}
