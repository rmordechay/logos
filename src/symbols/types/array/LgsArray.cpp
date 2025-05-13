#include "types/array/LgsArray.h"
#include "exprs/unary/LgsDArray.h"
#include "exprs/unary/LgsSArray.h"
#include "exprs/unary/constants/LgsIntConst.h"

void LgsArray::setBaseType(const vector<LgsExpr*>& exprs) {
    baseType = inferTypeFromIter(exprs);
}

LgsExpr* LgsArray::getZeroValue() {
    if (!isStatic) return new LgsDArray(baseType);
    const auto sArray = new LgsSArray(baseType);
    sArray->arrType.arrSize = arrSize;
    return sArray;
}

string LgsArray::prettyName() const {
    return name;
}

bool LgsArray::equals(LgsType* other) {
    const auto otherArr = other->asArray();
    if (!otherArr) return false;
    return baseType->equals(otherArr->baseType);
}

Type* LgsArray::getIRType() {
    if (!isStatic) return ptrTy;
    if (IRType) return IRType;
    IRType = baseType->getIRType();
    for (auto size = arrSize.rbegin(); size != arrSize.rend(); ++size) {
        IRType = ArrayType::get(IRType, (*size)->asIntConst()->value);
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
