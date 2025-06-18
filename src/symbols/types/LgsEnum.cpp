#include "types/LgsEnum.h"
#include "exprs/unary/LgsEnumField.h"
#include "logos/LgsRuntime.h"

LgsExpr* LgsEnum::getZeroValue() {
    return nullptr;
}

Type* LgsEnum::getIRType() {
    return PointerType::getUnqual(context);
}

string LgsEnum::getIRName() {
    return name;
}

string LgsEnum::prettyName() const {
    return name;
}

bool LgsEnum::equals(LgsType* other) {
    return name == other->getIRName();
}

string LgsEnum::getStrFormatPart() const {
    return "%s";
}
