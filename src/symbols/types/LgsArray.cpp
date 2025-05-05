#include "types/LgsArray.h"
#include "exprs/unary/LgsDArray.h"

LgsExpr* LgsArray::getZeroValue() {
    return new LgsDArray(underlyingType);
}

string LgsArray::prettyName() const {
    return name;
}

bool LgsArray::equals(LgsType* other) const {
    if (const auto otherSArrType = other->asArray()) {
        return getDims() == otherSArrType->getDims();
    }
    return false;
}

Type* LgsArray::getIRType() {
    if (!isStatic) return ptrTy;
    if (IRType) return IRType;
    IRType = underlyingType->getIRType();
    for (auto size = sizes.rbegin(); size != sizes.rend(); ++size) {
        IRType = ArrayType::get(IRType, *size);
    }
    return IRType;
}

string LgsArray::getIRName() {
    assert(false);
}

LgsType* LgsArray::inferBinaryType(LgsType* other) {
    assert(false);
}

bool LgsArray::isIndexable(LgsType* indexType) {
    return !!indexType->asInt();
}
