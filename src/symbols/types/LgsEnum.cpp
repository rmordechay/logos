#include "types/LgsEnum.h"

#include "utils/LgsIRUtils.h"
#include "utils/LgsUtils.h"

LgsExpr* LgsEnum::getZeroValue() {
    return nullptr;
}

Type* LgsEnum::getIRType(LgsModule* module) {
    return ptrTy(module);
}

string LgsEnum::getName() {
    return name;
}

string LgsEnum::prettyName() {
    return name;
}

bool LgsEnum::equals(LgsType* other) {
    return name == other->getName();
}

string LgsEnum::getStrFormatPart() const {
    return "%s";
}
