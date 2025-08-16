#include "types/LgsEnum.h"


#include "logos/LgsCodeGen.h"
#include "utils/LgsUtils.h"

LgsExpr* LgsEnum::getZeroValue() {
    return nullptr;
}

Type* LgsEnum::getIRType(LgsCodeGen* codeGen) {
    return codeGen->ptrTy();
}

std::string LgsEnum::getName() {
    return name;
}

std::string LgsEnum::pname() {
    return name;
}

bool LgsEnum::equals(LgsType* other) {
    return name == other->getName();
}

std::string LgsEnum::strFormatPart() const {
    return "%s";
}

size_t LgsEnum::getSizeBytes() {
    return 0;
}
