#include "types/primitives/LgsChar.h"

#include "exprs/LgsNull.h"
#include "exprs/unary/constants/LgsCharConst.h"

string LgsChar::prettyName() const {
    return name;
}

Type* LgsChar::getIRType() {
    return Type::getInt8Ty(context);
}

string LgsChar::getIRName() {
    return name;
}

LgsExpr* LgsChar::getZeroValue() {
    if (isNullable) return new LgsNull();
    return new LgsCharConst('0');
}

LgsType* LgsChar::inferBinaryType(LgsType* other) {
    return this;
}

string LgsChar::getStrFormatPart() const {
    return "%c";
}

bool LgsChar::equals(LgsType* other) {
    return name == other->getIRName();
}
