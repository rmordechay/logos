#include "types/primitives/LgsUInt.h"
#include "exprs/unary/constants/LgsUIntConst.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsSize.h"
#include "utils/LgsIRUtils.h"
#include "utils/LgsUtils.h"

size_t LgsUInt::getSizeBytes() {
    return sizeof(unsigned int);
}

string LgsUInt::prettyName() {
    return name;
}

Type* LgsUInt::getIRType(LgsModule* module) {
    return i32Ty(module);
}

string LgsUInt::getName() {
    return name;
}

LgsExpr* LgsUInt::getZeroValue() {
    return new LgsUIntConst(0);
}

bool LgsUInt::equals(LgsType* other) {
    const auto IRName = other->getName();
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsInt::name) return true;
    if (IRName == LgsSize::name) return true;
    return name == IRName;
}

string LgsUInt::getStrFormatPart() const {
    return "%d";
}
