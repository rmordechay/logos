#include "types/LgsGenericParam.h"
#include "types/LgsAny.h"

Type* LgsGenericParam::getIRType(LgsLLVMGen& cg) {
    assert(0);
}

size_t LgsGenericParam::sizeBytes() {
    assert(0);
}

LgsExpr* LgsGenericParam::getZeroValue() {
    assert(0);
}

Lgs_TypeKind LgsGenericParam::getRTTypeKind() {
    return RTT_STR;
}

std::string LgsGenericParam::getName() {
    return name;
}

bool LgsGenericParam::canCastTo(LgsType* other) {
    return true;
}

LgsGenericParam* LgsGenericParam::clone() {
    return new LgsGenericParam(*this);
}

std::string LgsGenericParam::strFormatPart() const {
    assert(0);
}
