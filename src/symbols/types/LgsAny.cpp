#include "types/LgsAny.h"

Type* LgsAny::getIRType() {
    return ptrTy;
}

LgsExpr* LgsAny::getZeroValue() {
    assert(false);
}

const string LgsAny::getName() const {
    return name;
}

bool LgsAny::equals(LgsType* other) const {
    assert(false);
}

LgsType* LgsAny::inferBinaryType(LgsType* other) {
    assert(false);
}
