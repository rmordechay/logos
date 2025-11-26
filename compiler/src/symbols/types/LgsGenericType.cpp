#include "types/LgsGenericType.h"
#include "types/LgsAny.h"

Type* LgsGenericType::getIRType(LgsLLVMGen& cg) {
    assert(0);
}

Constant* LgsGenericType::getRTType(LgsLLVMGen& cg) {
    assert(0);
}

size_t LgsGenericType::sizeBytes() {
    assert(0);
}

LgsExpr* LgsGenericType::getZeroValue() {
    assert(0);
}

std::string LgsGenericType::getName() {
    return name;
}

bool LgsGenericType::canCastTo(LgsType* other) {
    return true;
}

std::string LgsGenericType::strFormatPart() const {
    assert(0);
}

llvm::DIType* LgsGenericType::getDebugType(LgsLLVMGen& cg) {
    assert(0);
}

LgsGenericType* LgsGenericType::clone() {
    return new LgsGenericType(*this);
}
