#include "types/LgsAny.h"

Type* LgsAny::getIRType() {
    return ptrTy;
}

LgsExpr* LgsAny::getZeroValue() {
    assert(false);
}

const string LgsAny::getPrettyName() const {
    return name;
}

bool LgsAny::equals(LgsType* other) const {
    // TODO should everything equals Any?
    return true;
}

LgsType* LgsAny::inferBinaryType(LgsType* other) {
    assert(false);
}
