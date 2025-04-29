#include "types/LgsBool.h"

#include "exprs/LgsNull.h"
#include "exprs/unary/constants/LgsBoolConst.h"

const string LgsBool::getName() const {
    return name;
}

Type* LgsBool::getIRType() {
    return Type::getInt1Ty(context);
}

LgsExpr* LgsBool::getZeroValue() {
    if (nullable) return new LgsNull();
    return new LgsBoolConst(false);
}

LgsType* LgsBool::inferBinaryType(LgsType* other) {
    return this;
}

bool LgsBool::equals(LgsType* other) const {
    if (nullable) {
        return name == other->getName();
    }
    return name == other->getName();
}
