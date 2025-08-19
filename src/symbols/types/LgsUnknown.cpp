#include "types/LgsUnknown.h"

json::value_ref LgsUnknown::asJSON() {
    json::object obj;
    return obj;
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

bool LgsUnknown::equals(LgsType* other) {
    return false;
}

std::string LgsUnknown::strFormatPart() const {
    assert(0);
}

llvm::Type* LgsUnknown::getIRType(LgsCodeGen* codeGen) {
    assert(0);
}
