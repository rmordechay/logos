#include "types/LgsNullable.h"
#include "logos/LgsCodeGen.h"
#include "utils/LgsUtils.h"

Type* LgsNullable::getIRType(LgsCodeGen* codeGen) {
    return codeGen->ptrTy();
}

std::string LgsNullable::getName() {
    assert(0);
}

LgsExpr* LgsNullable::getZeroValue() {
    return baseType->getZeroValue();
}

std::string LgsNullable::pname() {
    return baseType->pname() + '?';
}

bool LgsNullable::equals(LgsType* other) {
    return baseType->equals(other);
}

size_t LgsNullable::getSizeBytes() {
    return 0;
}

LgsNullable::~LgsNullable() {
    if (baseType) {
        freeType(baseType);
        baseType = nullptr;
    }
}
