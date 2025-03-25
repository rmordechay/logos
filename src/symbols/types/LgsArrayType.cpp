#include "types/LgsArrayType.h"

#include <llvm/IR/DerivedTypes.h>

const string LgsArrayType::getName() const {
    return underlyingType->getName() + "[]";
}

Type* LgsArrayType::getIRType(const int size) {
    return ArrayType::get(underlyingType->getIRType(), size);
}

LgsConst* LgsArrayType::getZeroValue() {
    assert(false && "not implemented");
}

bool LgsArrayType::equals(LgsType* other) const {
    assert(false && "not implemented");
}

LgsType* LgsArrayType::inferBinaryType(LgsType* other) {
    assert(false && "not implemented");
}