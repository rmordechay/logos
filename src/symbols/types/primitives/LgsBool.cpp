
#include "exprs/unary/constants/LgsBoolConst.h"
#include "exprs/LgsNullValue.h"

string LgsBool::prettyName() const {
    return name;
}

Type* LgsBool::getIRType(LgsModule* module) {
    return Type::getInt1Ty(module->context);
}

string LgsBool::getIRName() {
    return name;
}

LgsExpr* LgsBool::getZeroValue() {
    return new LgsBoolConst(false);
}

bool LgsBool::equals(LgsType* other) {
    if (asNullable()) {
        return name == other->getIRName();
    }
    return name == other->getIRName();
}

string LgsBool::getStrFormatPart() const {
    return "%d";
}
