#include "types/LgsInterface.h"


size_t LgsInterface::size() {
    return sizeof(void*);
}

const string LgsInterface::getName() const {
    return name;
}

Type* LgsInterface::getIRType() {
    assert(false);
}

LgsExpr* LgsInterface::getZeroValue() {
    assert(false && "not implemented");
}

bool LgsInterface::equals(LgsType* other) const {
    assert(false && "not implemented");
}

LgsType* LgsInterface::inferBinaryType(LgsType* other) {
    assert(false && "not implemented");
}
