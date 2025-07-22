

#include "exprs/LgsNullValue.h"
#include "exprs/unary/constants/LgsCharConst.h"

string LgsChar::prettyName() const {
    return name;
}

size_t LgsChar::getSizeBytes() {
    return sizeof(char);
}

Type* LgsChar::getIRType(LgsModule* module) {
    return Type::getInt8Ty(module->context);
}

string LgsChar::getIRName() {
    return name;
}

LgsExpr* LgsChar::getZeroValue() {
    return new LgsCharConst('0');
}

string LgsChar::getStrFormatPart() const {
    return "%c";
}

bool LgsChar::equals(LgsType* other) {
    return name == other->getIRName();
}