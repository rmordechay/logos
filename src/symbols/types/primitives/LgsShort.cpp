#include "exprs/LgsNullValue.h"
#include "exprs/unary/constants/LgsShortConst.h"
#include "types/LgsAny.h"

size_t LgsShort::getSizeBytes() {
    return sizeof(short);
}

Type* LgsShort::getIRType(LgsModule* module) {
    return Type::getInt16Ty(module->context);
}

string LgsShort::prettyName() {
    return name;
}

string LgsShort::getName() {
    return name;
}

LgsExpr* LgsShort::getZeroValue() {
    return new LgsShortConst(0);
}

bool LgsShort::equals(LgsType* other) {
    if (other->getName() == LgsAny::name) return true;
    return name == other->getName();
}

string LgsShort::getStrFormatPart() const {
    return "%d";
}