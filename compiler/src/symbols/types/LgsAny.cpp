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

LgsType* LgsAny::applyBinOp(LgsType* toType, LgsBinOp& op) {
    assert(0);
}

bool LgsAny::canCastTo(LgsType*) {
    return true;
}

DIType* LgsAny::getDebugType(LgsCgModule& cg) {
    assert(0);
}