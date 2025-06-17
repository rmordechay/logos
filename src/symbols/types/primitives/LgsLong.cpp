#include "types/primitives/LgsLong.h"

#include "exprs/unary/constants/LgsLongConst.h"
#include "logos/LgsRuntime.h"
#include "types/LgsAny.h"
#include "types/LgsPtr.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsSize.h"

string LgsLong::prettyName() const {
    return name;
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

string LgsLong::getIRName() {
    return name;
}

bool LgsLong::equals(LgsType* other) {
    const auto IRName = other->getIRName();
    if (IRName == LgsPtr::name) return true;
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsFloat::name) return true;
    if (IRName == LgsSize::name) return true;
    return name == IRName;
}

string LgsLong::getStrFormatPart() const {
    return "%lu";
}
