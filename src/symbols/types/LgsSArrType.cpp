#include "types/LgsSArrType.h"
#include "exprs/unary/LgsSArray.h"

Type* LgsSArrType::getIRType() {
    if (IRType) return IRType;
    IRType = getUnderlyingIRType();
    return IRType;
}

Type* LgsSArrType::getUnderlyingIRType() {
    if (IRType) return IRType;
    IRType = underlyingType->getIRType();
    for (auto it = iterableSize.rbegin(); it != iterableSize.rend(); ++it) {
        IRType = ArrayType::get(IRType, *it);
    }
    return IRType;
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
