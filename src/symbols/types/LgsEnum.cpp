#include "types/LgsEnum.h"
#include "codegen/LgsLLVMGen.h"
#include "stmts/LgsField.h"
#include "types/LgsAny.h"
#include "utils/LgsUtils.h"

LgsExpr* LgsEnum::getZeroValue() {
    return nullptr;
}

Lgs_RTType LgsEnum::getRTType() {
    return RTT_ENUM;
}

Type* LgsEnum::getIRType(LgsLLVMGen& cg) {
    return cg.ptrTy();
}

std::string LgsEnum::getName() {
    return name;
}

bool LgsEnum::canCastTo(LgsType* other) {
    const auto otherName = other->getName();
    if (otherName == LgsAny::name) return true;
    return name == otherName;
}

std::string LgsEnum::strFormatPart() const {
    return "%s";
}

size_t LgsEnum::getSizeBytes() {
    return sizeof(void*);
}

LgsEnum* LgsEnum::clone() {
    return new LgsEnum(*this);
}
