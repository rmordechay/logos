#include "types/primitives/LgsUInt.h"
#include "exprs/constants/LgsIntConst.h"
#include "codegen/LgsCgModule.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsSize.h"

size_t LgsUInt::sizeBytes() {
    return sizeof(uint32_t);
}

Type* LgsUInt::getIRType(LgsCgModule& cg) {
    return cg.i32Ty();
}

Constant* LgsUInt::getRTType(LgsCgModule& cg) {
    return cg.getRTTypeInfo(getGenericName(), sizeBytes(), RTT_UINT, cg.null());
}

std::string LgsUInt::getName() {
    return name;
}

LgsExpr* LgsUInt::getZeroValue() {
    return new LgsIntConst(this, 0);
}

bool LgsUInt::canCastTo(LgsType* other) {
    const auto IRName = other->getName();
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsInt::name) return true;
    if (IRName == LgsSize::name) return true;
    return name == IRName;
}

llvm::DIType* LgsUInt::getDebugType(LgsCgModule& cg) {
    assert(0);
}

LgsType* LgsUInt::clone() {
    return this;
}

std::string LgsUInt::strFormatPart() const {
    return "%d";
}
