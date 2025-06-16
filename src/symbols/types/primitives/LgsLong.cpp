#include "types/primitives/LgsLong.h"

#include "exprs/unary/constants/LgsLongConst.h"
#include "logos/LgsRuntime.h"
#include "types/LgsAny.h"

string LgsLong::prettyName() const {
    return name;
}

bool LgsLong::equals(LgsType* other) {
    if (other->getIRName() == LgsAny::name) return true;
    return name == other->getIRName();
}

Type* LgsLong::getIRType() {
    return Type::getInt64Ty(context);
}

size_t LgsLong::getSizeBytes() {
    return sizeof(long);
}

LgsExpr* LgsLong::getZeroValue() {
    return new LgsLongConst(0);
}

string LgsLong::getStrFormatPart() const {
    return "%lu";
}

string LgsLong::getIRName() {
    return name;
}
