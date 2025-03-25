#include "types/LgsArrayType.h"

#include <llvm/IR/DerivedTypes.h>

const string LgsArrayType::getName() const {
    return underlyingType->getName() + "[]";
}

Type* LgsArrayType::getIRType(const int size) {
    return ArrayType::get(underlyingType->getIRType(), size);
}

LgsExpr* LgsArrayType::getZeroValue() {
    assert(false && "not implemented");
}

bool LgsArrayType::equals(LgsType* other) const {
    if (const auto otherArrayType = dynamic_cast<LgsArrayType*>(other)) {
        return underlyingType->equals(otherArrayType->underlyingType);
    }
    return false;
}

LgsType* LgsArrayType::inferBinaryType(LgsType* other) {
    assert(false && "not implemented");
}