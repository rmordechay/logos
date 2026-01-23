#include "types/LgsAny.h"
#include "codegen/LgsCodeGen.h"

size_t LgsAny::sizeBytes() {
    return sizeof(void*);
}

Type* LgsAny::getIRType(LgsCodeGen& cg) {
    return cg.ptrTy();
}

Constant* LgsAny::getRTType(LgsCodeGen& cg) {
    assert(0);
}

std::string LgsAny::getName() {
    return name;
}

LgsExpr* LgsAny::getZeroValue() {
    assert(0);
}

std::string LgsAny::fmtStr() const {
    return "%p";
}

LgsType* LgsAny::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    assert(0);
}

bool LgsAny::canCastTo(LgsType*) {
    return true;
}

DIType* LgsAny::getDebugType(LgsCodeGen& cg) {
    assert(0);
}