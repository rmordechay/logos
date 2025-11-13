#include "types/LgsGenericType.h"
#include "types/LgsAny.h"

Type* LgsGenericType::getIRType(LgsLLVMGen& cg) {
    assert(0);
}

size_t LgsGenericType::sizeBytes() {
    assert(0);
}

LgsExpr* LgsGenericType::getZeroValue() {
    assert(0);
}

Lgs_TypeKind LgsGenericType::getRTTypeKind() {
    return RTT_STR;
}

std::string LgsGenericType::getName() {
    return name;
}

bool LgsGenericType::canCastTo(LgsType* other) {
    return true;
}

LgsGenericType* LgsGenericType::clone() {
    return new LgsGenericType(*this);
}

std::string LgsGenericType::strFormatPart() const {
    assert(0);
}
