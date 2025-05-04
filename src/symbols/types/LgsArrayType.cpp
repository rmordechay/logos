#include "types/LgsArrayType.h"

#include "exprs/unary/LgsDArray.h"
#include "exprs/unary/LgsSArray.h"

Type* LgsArrayType::getIRType() {
    if (!isStatic) return ptrTy;
    if (IRType) return IRType;
    IRType = underlyingType->getIRType();
    for (auto it = sizes.rbegin(); it != sizes.rend(); ++it) {
        IRType = ArrayType::get(IRType, *it);
    }
    return IRType;
}

LgsExpr* LgsArrayType::getZeroValue() {
    if (isStatic) {
        const auto sArrType = new LgsSArray(underlyingType);
        sArrType->type = this;
        return sArrType;
    }
    const auto dArrType = new LgsDArray(underlyingType);
    dArrType->type = this;
    return dArrType;
}

const string LgsArrayType::getName() const {
    return name;
}

bool LgsArrayType::equals(LgsType* other) const {
    if (isStatic) {
        if (const auto otherSArrType = other->asSArrayType()) {
            return sizes.size() == otherSArrType->sizes.size();
        }
        return false;
    }
    assert(false);
}

LgsType* LgsArrayType::inferBinaryType(LgsType* other) {
    assert(false);
}
