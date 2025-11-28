#include "types/LgsAny.h"
#include "codegen/LgsCgModule.h"

size_t LgsAny::sizeBytes() {
    return sizeof(void*);
}

Type* LgsAny::getIRType(LgsCgModule& cg) {
    return cg.ptrTy();
}

Constant* LgsAny::getRTType(LgsCgModule& cg) {
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

llvm::DIType* LgsAny::getDebugType(LgsCgModule& cg) {
    assert(0);
}

LgsType* LgsAny::clone() {
    return this;
}
