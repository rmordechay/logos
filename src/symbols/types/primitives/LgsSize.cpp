#include "types/primitives/LgsSize.h"


#include "utils/LgsUtils.h"

size_t LgsSize::getSizeBytes() {
    return sizeof(size_t);
}

Type* LgsSize::getIRType(LgsCodeGen* codeGen) {
    return codeGen->sizeTy();
}

std::string LgsSize::getName() {
    return name;
}

std::string LgsSize::prettyName() {
    return name;
}

LgsExpr* LgsSize::getZeroValue() {
    assert(0);
}

bool LgsSize::equals(LgsType* other) {
    assert(0);
}

std::string LgsSize::getStrFormatPart() const {
    return "%zu";
}