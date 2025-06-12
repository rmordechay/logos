
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

LgsExpr* LgsBool::getZeroValue() {
    if (hasFlag(NULLABLE)) return new LgsNull();
    return new LgsBoolConst(false);
}

LgsType* LgsBool::inferBinaryType(LgsType* other) {
    return this;
}

bool LgsBool::equals(LgsType* other) {
    if (hasFlag(NULLABLE)) {
        return name == other->getIRName();
    }
    return name == other->getIRName();
}

string LgsBool::getStrFormatPart() const {
    return "%d";
}
