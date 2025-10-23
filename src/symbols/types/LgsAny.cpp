#include "types/LgsAny.h"
#include "codegen/LgsLLVMGen.h"

size_t LgsAny::getSizeBytes() {
    return sizeof(void*);
}

Type* LgsAny::getIRType(LgsLLVMGen& cg) {
    return cg.ptrTy();
}

std::string LgsAny::getName() {
    return name;
}

LgsExpr* LgsAny::getZeroValue() {
    assert(0);
}

Lgs_rttype LgsAny::getRTType() {
    return RTT_ANY;
}

std::string LgsAny::strFormatPart() const {
    return "%p";
}

bool LgsAny::canCastTo(LgsType*) {
    return true;
}
