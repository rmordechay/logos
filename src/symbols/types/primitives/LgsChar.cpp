

#include "exprs/LgsNull.h"
#include "exprs/unary/constants/LgsCharConst.h"

string LgsChar::prettyName() const {
    return name;
}

size_t LgsChar::getSizeBytes() {
    return sizeof(char);
}

Type* LgsChar::getIRType() {
    return Type::getInt8Ty(context);
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