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

std::string LgsGenericParam::getName() {
    return name;
}

bool LgsGenericParam::canCastTo(LgsType* other) {
    return true;
}

std::string LgsGenericParam::strFormatPart() const {
    assert(0);
}

llvm::DIType* LgsGenericParam::getDebugType(LgsLLVMGen& cg) {
    assert(0);
}

LgsGenericParam* LgsGenericParam::clone() {
    return new LgsGenericParam(*this);
}
