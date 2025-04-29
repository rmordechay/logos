#include "types/LgsInterface.h"

const string LgsInterface::getName() const {
    return name;
}

Type* LgsInterface::getIRType() {
    return ptrTy;
}

LgsExpr* LgsInterface::getZeroValue() {
    assert(false);
}

bool LgsInterface::equals(LgsType* other) const {
    assert(false);
}

LgsType* LgsInterface::inferBinaryType(LgsType* other) {
    assert(false);
}
