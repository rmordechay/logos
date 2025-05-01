#include "types/LgsSArrType.h"
#include "exprs/unary/LgsSArray.h"

Type* LgsSArrType::getIRType() {
    assert(false);
}

Type* LgsSArrType::getUnderlyingIRType() {
    Type *arrayTy = underlyingType->getIRType();
    for (auto it = iterableSize.rbegin(); it != iterableSize.rend(); ++it) {
        arrayTy = ArrayType::get(arrayTy, *it);
    }
    return arrayTy;
}

LgsExpr* LgsSArrType::getZeroValue() {
    return new LgsSArray(underlyingType, iterableSize);
}

const string LgsSArrType::getName() const {
    return name;
}

bool LgsSArrType::equals(LgsType* other) const {
    return underlyingType->equals(other);
}

LgsType* LgsSArrType::inferBinaryType(LgsType* other) {
    assert(false);
}
