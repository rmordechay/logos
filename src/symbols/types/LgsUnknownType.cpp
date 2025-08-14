#include "types/LgsUnknownType.h"

std::string LgsUnknownType::prettyName() {
    return getName();
}

std::string LgsUnknownType::getName() {
    return name == "" ? genricName : name;
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

Type* LgsUnknownType::getIRType(LgsCodeGen* codeGen) {
    assert(0);
}