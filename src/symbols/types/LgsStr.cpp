#include "types/LgsStr.h"

#include "exprs/unary/constants/LgsConst.h"
#include "exprs/unary/constants/LgsStrConst.h"

const string LgsStr::getName() const {
    return name;
}

Type* LgsStr::getIRType() {
    return PointerType::get(Type::getInt8Ty(context), 0);
}

LgsConst* LgsStr::getZeroValue() {
    return new LgsStrConst("");
}

LgsType* LgsStr::inferBinaryType(LgsType* other) {
    return this;
}

bool LgsStr::equals(LgsType* other) const {
    return name == other->getName();
}
