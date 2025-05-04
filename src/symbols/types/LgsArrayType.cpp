#include "types/LgsArrayType.h"

#include "exprs/unary/LgsDArray.h"
#include "exprs/unary/LgsSArray.h"

LgsExpr* LgsArrayType::getZeroValue() {
    if (isStatic) return new LgsSArray(underlyingType, sizes);
    return new LgsDArray(underlyingType);
}

const string LgsArrayType::getName() const {
    return name;
}

bool LgsArrayType::equals(LgsType* other) const {
    if (isStatic) {
        if (const auto otherSArrType = other->asSArrayType()) {
            return getDims() == otherSArrType->getDims();
        }
        return false;
    }
    assert(false);
}

LgsType* LgsArrayType::inferBinaryType(LgsType* other) {
    assert(false);
}
