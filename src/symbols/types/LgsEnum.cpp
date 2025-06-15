#include "types/LgsEnum.h"

#include "exprs/unary/LgsEnumField.h"
#include "logos/LgsRuntime.h"
#include "stmts/LgsField.h"

LgsExpr* LgsEnum::getZeroValue() {
    return new LgsDefaultEnumField(this);
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
