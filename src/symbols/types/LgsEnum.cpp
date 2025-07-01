#include "types/LgsEnum.h"
#include "exprs/unary/LgsEnumField.h"
#include "logos/LgsModule.h"

LgsExpr* LgsEnum::getZeroValue() {
    return nullptr;
}

Type* LgsEnum::getIRType(LLVMContext& context) {
    return ptrTy(context);
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
