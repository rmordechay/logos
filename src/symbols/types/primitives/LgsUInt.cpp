#include "types/primitives/LgsUInt.h"
#include "exprs/LgsNull.h"
#include "exprs/unary/constants/LgsUIntConst.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsSize.h"

size_t LgsUInt::getSizeBytes() {
    return sizeof(unsigned int);
}

string LgsUInt::prettyName() const {
    return name;
}

Type* LgsUInt::getIRType() {
    return Type::getInt32Ty(context);
}

string LgsUInt::getIRName() {
    return name;
}

LgsExpr* LgsUInt::getZeroValue() {
    if (isNullable) return new LgsNull();
    return new LgsUIntConst(0);
}

LgsType* LgsUInt::inferBinaryType(LgsType* other) {
    return this;
}

bool LgsUInt::equals(LgsType* other) {
    if (other->getIRName() == LgsAny::name) return true;
    if (other->getIRName() == LgsSize::name) return true;
    return name == other->getIRName();
}

string LgsUInt::getStrFormatPart() const {
    return "%d";
}

LgsType* LgsUInt::clone() {
    return this;
}
