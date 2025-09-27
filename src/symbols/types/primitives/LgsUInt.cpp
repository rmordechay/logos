#include "types/primitives/LgsUInt.h"
#include "exprs/constants/LgsIntConst.h"
#include "../codegen/LgsLLVMGen.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsSize.h"

size_t LgsUInt::getSizeBytes() {
    return sizeof(uint32_t);
}

json::value LgsUInt::asJsonStr() {
    assert(0);
}

Type* LgsUInt::getIRType(LgsLLVMGen& cg) {
    return cg.i32Ty();
}

std::string LgsUInt::getName() {
    return name;
}

LgsExpr* LgsUInt::getZeroValue() {
    return new LgsIntConst(this, 0);
}

Lgs_RTType LgsUInt::getRTType() {
    return RTT_UINT;
}

bool LgsUInt::canCastTo(LgsType* other) {
    const auto IRName = other->getName();
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsInt::name) return true;
    if (IRName == LgsSize::name) return true;
    return name == IRName;
}

std::string LgsUInt::strFormatPart() const {
    return "%d";
}
