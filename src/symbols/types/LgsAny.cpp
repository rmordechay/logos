#include "types/LgsAny.h"

Type* LgsAny::getIRType() {
    return ptrTy;
}

string LgsAny::getIRName() {
    return name;
}

LgsExpr* LgsAny::getZeroValue() {
    assert(false);
}

string LgsAny::prettyName() const {
    return name;
}

bool LgsAny::equals(LgsType* other) {
    // TODO should everything equals Any?
    return true;
}

LgsType* LgsAny::inferBinaryType(LgsType* other) {
    assert(false);
}
