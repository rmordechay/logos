#include "types/LgsUnknownType.h"

std::string LgsUnknownType::pname() {
    return getName();
}

std::string LgsUnknownType::getName() {
    return name;
}

LgsExpr* LgsUnknownType::getZeroValue() {
    assert(0);
}

size_t LgsUnknownType::getSizeBytes() {
    return 0;
}

bool LgsUnknownType::equals(LgsType* other) {
    return false;
}

llvm::Type* LgsUnknownType::getIRType(LgsCodeGen* codeGen) {
    assert(0);
}