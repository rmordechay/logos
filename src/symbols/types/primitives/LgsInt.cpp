#include "exprs/LgsNullValue.h"
#include "exprs/unary/constants/LgsIntConst.h"
#include "stmts/LgsField.h"
#include "types/LgsAny.h"
#include "types/LgsPtr.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsSize.h"
#include "types/primitives/LgsUInt.h"

size_t LgsInt::getSizeBytes() {
    return sizeof(int);
}

string LgsInt::prettyName() {
    return name;
}

Type* LgsInt::getIRType(LgsModule* module) {
    return Type::getInt32Ty(module->context);
}

string LgsInt::getName() {
    return name;
}

LgsExpr* LgsInt::getZeroValue() {
    return new LgsIntConst(0);
}

bool LgsInt::equals(LgsType* other) {
    const auto IRName = other->getName();
    if (IRName == LgsPtr::name) return true;
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsFloat::name) return true;
    if (IRName == LgsUInt::name) return true;
    if (IRName == LgsSize::name) return true;
    return name == IRName;
}

string LgsInt::getStrFormatPart() const {
    return "%d";
}
