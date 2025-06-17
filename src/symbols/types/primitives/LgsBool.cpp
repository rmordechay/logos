
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
    if (isNullable) return &LGS_NULL;
    return new LgsBoolConst(false);
}

bool LgsBool::equals(LgsType* other) {
    if (isNullable) {
        return name == other->getIRName();
    }
    return name == other->getIRName();
}

string LgsBool::getStrFormatPart() const {
    return "%d";
}
