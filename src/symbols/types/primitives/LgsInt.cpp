#include "exprs/LgsNull.h"
#include "exprs/unary/constants/LgsIntConst.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsSize.h"
#include "types/primitives/LgsUInt.h"

size_t LgsInt::getSizeBytes() {
    return sizeof(int);
}

string LgsInt::prettyName() const {
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

bool LgsInt::equals(LgsType* other) {
    const auto IRName = other->getIRName();
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsSize::name) return true;
    return name == IRName;
}

string LgsInt::getStrFormatPart() const {
    return "%d";
}
