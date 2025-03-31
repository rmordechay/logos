#include "types/LgsInterface.h"


const string LgsInterface::getName() const {
    return name;
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
