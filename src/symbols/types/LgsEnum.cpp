#include "types/LgsEnum.h"
#include "codegen/LgsLLVMGen.h"

LgsExpr* LgsEnum::getZeroValue() {
    return nullptr;
}

Lgs_RTType LgsEnum::getRTType() {
    assert(0);
}

Type* LgsEnum::getIRType(LgsLLVMGen& cg) {
    return cg.ptrTy();
}

std::string LgsEnum::getName() {
    return name;
}

json::value LgsEnum::asJSON() {
    assert(0);
}

std::string LgsEnum::pname() {
    return name;
}

bool LgsEnum::canCastTo(LgsType* other) {
    return name == other->getName();
}

std::string LgsEnum::strFormatPart() const {
    return "%s";
}

size_t LgsEnum::getSizeBytes() {
    return sizeof(void*);
}
