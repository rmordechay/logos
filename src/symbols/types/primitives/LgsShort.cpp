#include "exprs/LgsNull.h"
#include "exprs/unary/constants/LgsShortConst.h"
#include "types/LgsAny.h"

size_t LgsShort::getSizeBytes() {
    return sizeof(short);
}

Type* LgsShort::getIRType() {
    return Type::getInt16Ty(context);
}

string LgsShort::prettyName() const {
    return name;
}

string LgsShort::getIRName() {
    return name;
}

LgsExpr* LgsShort::getZeroValue() {

    return new LgsShortConst(0);
}

bool LgsShort::equals(LgsType* other) {
    if (other->getIRName() == LgsAny::name) return true;
    return name == other->getIRName();
}

string LgsShort::getStrFormatPart() const {
    return "%d";
}