#include "types/LgsEnum.h"

LgsExpr* LgsEnum::getZeroValue() {
    assert(false);
}

const string LgsEnum::getName() const {
    return name;
}

bool LgsEnum::equals(LgsType* other) const {
    return name == other->getName();
}

LgsType* LgsEnum::inferBinaryType(LgsType* other) {
    assert(false);
}
