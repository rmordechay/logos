#include "types/LgsArray.h"
#include "exprs/unary/LgsDArray.h"
#include "exprs/unary/LgsSArray.h"

void LgsArray::setUnderlyingType(const vector<LgsExpr*>& exprs) {
    underlyingType = inferTypeFromIter(exprs);
}

LgsExpr* LgsArray::getZeroValue() {
    if (!isStaticIter) return new LgsDArray(underlyingType);
    const auto sArray = new LgsSArray(underlyingType);
    sArray->arrType.sizes = sizes;
    return sArray;
}

string LgsArray::prettyName() const {
    return name;
}

bool LgsArray::equals(LgsType* other) const {
    const auto otherArr = other->asArray();
    if (!otherArr) return false;
    return underlyingType->equals(otherArr->underlyingType);
}

Type* LgsArray::getIRType() {
    if (!isStaticIter) return ptrTy;
    if (IRType) return IRType;
    IRType = underlyingType->getIRType();
    for (auto size = sizes.rbegin(); size != sizes.rend(); ++size) {
        IRType = ArrayType::get(IRType, *size);
    }
    return IRType;
}

string LgsArray::getIRName() {
    return name;
}

LgsType* LgsArray::inferBinaryType(LgsType* other) {
    assert(false);
}

bool LgsArray::isIndexable(LgsType* indexType) {
    return !!indexType->asInt();
}
