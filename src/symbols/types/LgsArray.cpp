#include "types/LgsArray.h"
#include "exprs/unary/LgsDArray.h"
#include "exprs/unary/LgsSArray.h"

LgsExpr* LgsArray::getZeroValue() {
    if (isStatic) return new LgsSArray(underlyingType, sizes);
    return new LgsDArray(underlyingType);
}

const string LgsArray::getName() const {
    return name;
}

bool LgsArray::equals(LgsType* other) const {
    if (isStatic) {
        if (const auto otherSArrType = other->asSArrayType()) {
            return getDims() == otherSArrType->getDims();
        }
        return false;
    }
    assert(false);
}

LgsType* LgsArray::inferBinaryType(LgsType* other) {
    assert(false);
}
