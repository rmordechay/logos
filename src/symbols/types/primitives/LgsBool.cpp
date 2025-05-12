#include "types/primitives/LgsBool.h"
#include "exprs/unary/constants/LgsBoolConst.h"
#include "exprs/LgsNull.h"

string LgsBool::prettyName() const {
    return name;
}

Type* LgsBool::getIRType() {
    return Type::getInt1Ty(context);
}

string LgsBool::getIRName() {
    return name;
}

string LgsBool::getStrFormatPart() {
    return "%d";
}

LgsExpr* LgsBool::getZeroValue() {
    if (isNullable) return new LgsNull();
    return new LgsBoolConst(false);
}

LgsType* LgsBool::inferBinaryType(LgsType* other) {
    return this;
}

bool LgsBool::equals(LgsType* other) {
    if (isNullable) {
        return name == other->getIRName();
    }
    return name == other->getIRName();
}
