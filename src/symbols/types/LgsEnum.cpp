#include "types/LgsEnum.h"
#include "exprs/unary/LgsEnumField.h"
#include "logos/LgsRuntime.h"

LgsExpr* LgsEnum::getZeroValue() {
    return getField(LOGOS_DEFAULT_ENUM)->expr;
}

Type* LgsEnum::getIRType() {
    return PointerType::getUnqual(context);
}

string LgsEnum::getIRName() {
    return name;
}

string LgsEnum::pName() const {
    return name;
}

bool LgsEnum::equals(LgsType* other) {
    return name == other->getIRName();
}

LgsType* LgsEnum::inferBinaryType(LgsType* other) {
    assert(0);
}
