#include "types/LgsUnknownType.h"

json::object LgsUnknownType::asJSON() {
    json::object obj;
    return obj;
}

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

std::string LgsUnknownType::strFormatPart() const {
    assert(0);
}

llvm::Type* LgsUnknownType::getIRType(LgsCodeGen* codeGen) {
    assert(0);
}
