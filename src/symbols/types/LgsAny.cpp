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

Lgs_RTType LgsAny::getRTType() {
    return RTT_ANY;
}

json::value LgsAny::asJsonStr() {
    assert(0);
}

std::string LgsAny::strFormatPart() const {
    return "%p";
}

bool LgsAny::canCastTo(LgsType* other) {
    return true;
}
