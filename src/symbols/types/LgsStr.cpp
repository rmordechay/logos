#include "types/LgsStr.h"

#include "exprs/LgsNull.h"
#include "exprs/unary/constants/LgsConstExpr.h"
#include "exprs/unary/constants/LgsStrConst.h"

const string LgsStr::getName() const {
    return name;
}

Type* LgsStr::getIRType() {
    return ptrTy;
}

LgsExpr* LgsStr::getZeroValue() {
    if (nullable) return new LgsNull();
    return new LgsStrConst("");
}

LgsType* LgsStr::inferBinaryType(LgsType* other) {
    return this;
}

bool LgsStr::equals(LgsType* other) const {
    return name == other->getName();
}
