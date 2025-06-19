#include "types/primitives/LgsUInt.h"
#include "exprs/LgsNull.h"
#include "exprs/unary/constants/LgsUIntConst.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsInt.h"
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

    return new LgsUIntConst(0);
}

bool LgsUInt::equals(LgsType* other) {
    const auto IRName = other->getIRName();
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsInt::name) return true;
    if (IRName == LgsSize::name) return true;
    return name == IRName;
}

string LgsUInt::getStrFormatPart() const {
    return "%d";
}
