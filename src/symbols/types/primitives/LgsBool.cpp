
#include "exprs/unary/constants/LgsBoolConst.h"
#include "exprs/LgsNullValue.h"

string LgsBool::prettyName() {
    return name;
}

Type* LgsBool::getIRType(LgsModule* module) {
    return Type::getInt1Ty(module->context);
}

string LgsBool::getName() {
    return name;
}

LgsExpr* LgsBool::getZeroValue() {
    return new LgsBoolConst(false);
}

bool LgsBool::equals(LgsType* other) {
    if (asNullable()) {
        return name == other->getName();
    }
    return name == other->getName();
}

string LgsBool::getStrFormatPart() const {
    return "%d";
}
