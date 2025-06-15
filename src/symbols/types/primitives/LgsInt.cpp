
#include "exprs/LgsNull.h"
#include "exprs/unary/constants/LgsIntConst.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsSize.h"
#include "types/primitives/LgsUInt.h"

size_t LgsInt::getSizeBytes() {
    return sizeof(int);
}

string LgsInt::pName() const {
    return name;
}

Type* LgsInt::getIRType() {
    return Type::getInt32Ty(context);
}

string LgsInt::getIRName() {
    return name;
}

LgsExpr* LgsInt::getZeroValue() {
    if (isNullable) return new LgsNull();
    return new LgsIntConst(0);
}

LgsType* LgsInt::inferBinaryType(LgsType* other) {
    return this;
}

bool LgsInt::equals(LgsType* other) {
    if (other->getIRName() == LgsAny::name) return true;
    if (other->getIRName() == LgsUInt::name) return true;
    if (other->getIRName() == LgsSize::name) return true;
    return name == other->getIRName();
}

string LgsInt::getStrFormatPart() const {
    return "%d";
}