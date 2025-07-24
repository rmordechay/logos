#include "types/primitives/LgsLong.h"

#include "exprs/unary/constants/LgsLongConst.h"
#include "logos/LgsModule.h"
#include "types/LgsAny.h"
#include "types/LgsPtr.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsSize.h"

string LgsLong::prettyName() {
    return name;
}

Type* LgsLong::getIRType(LgsModule* module) {
    return Type::getInt64Ty(module->context);
}

size_t LgsLong::getSizeBytes() {
    return sizeof(long);
}

LgsExpr* LgsLong::getZeroValue() {
    return new LgsLongConst(0);
}

string LgsLong::getName() {
    return name;
}

bool LgsLong::equals(LgsType* other) {
    const auto IRName = other->getName();
    if (IRName == LgsPtr::name) return true;
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsFloat::name) return true;
    if (IRName == LgsSize::name) return true;
    return name == IRName;
}

string LgsLong::getStrFormatPart() const {
    return "%lu";
}
