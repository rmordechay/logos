#include "types/LgsEnum.h"


#include "logos/LgsCodeGen.h"
#include "utils/LgsUtils.h"

LgsExpr* LgsEnum::getZeroValue() {
    return nullptr;
}

Type* LgsEnum::getIRType(LgsCodeGen* codeGen) {
    return codeGen->ptrTy();
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
