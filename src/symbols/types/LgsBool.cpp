#include "types/LgsBool.h"

#include "exprs/LgsNull.h"
#include "exprs/unary/constants/LgsBoolConst.h"

string LgsBool::prettyName() const {
    return name;
}

Type* LgsBool::getIRType() {
    return Type::getInt1Ty(context);
}

string LgsBool::getIRName() {
    return name;
}

LgsExpr* LgsBool::getZeroValue() {
    if (isNullable) return new LgsNull();
    return new LgsBoolConst(false);
}

LgsType* LgsBool::inferBinaryType(LgsType* other) {
    return this;
}

bool LgsBool::equals(LgsType* other) const {
    if (isNullable) {
        return name == other->getIRName();
    }
    return name == other->getIRName();
}
