#include "types/LgsAny.h"
#include "codegen/LgsLLVMGen.h"

size_t LgsAny::sizeBytes() {
    return sizeof(void*);
}

Type* LgsAny::getIRType(LgsLLVMGen& cg) {
    return cg.ptrTy();
}

Constant* LgsAny::getRTType(LgsLLVMGen& cg) {
    assert(0);
}

std::string LgsAny::getName() {
    return name;
}

LgsExpr* LgsAny::getZeroValue() {
    assert(0);
}

std::string LgsAny::strFormatPart() const {
    return "%p";
}

bool LgsAny::canCastTo(LgsType*) {
    return true;
}

llvm::DIType* LgsAny::getDebugType(LgsLLVMGen& cg) {
    assert(0);
}

LgsType* LgsAny::clone() {
    return this;
}
