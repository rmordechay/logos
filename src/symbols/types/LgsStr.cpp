#include "types/LgsStr.h"

#include "constants/LgsConst.h"
#include "constants/LgsStrConst.h"

const string LgsStr::getName() const {
    return name;
}

Type* LgsStr::getIRType() {
    return IRType;
}

LgsConst* LgsStr::getZeroValue() {
    return new LgsStrConst("");
}

LgsType* LgsStr::inferBinaryType(LgsType* other) const {
    return other;
}

bool LgsStr::equals(LgsType* other) const {
    return name == other->getName();
}
