#include "types/primitives/LgsShort.h"
#include "exprs/constants/LgsIntConst.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsLong.h"
#include "types/primitives/LgsSize.h"
#include "types/primitives/LgsUInt.h"

size_t LgsShort::sizeBytes() {
    return sizeof(short);
}

Type* LgsShort::getIRType(LgsCgModule& cg) {
    return cg.i16Ty();
}

Constant* LgsShort::getRTType(LgsCgModule& cg) {
    return cg.getRTTypeInfo(getGenericName(), sizeBytes(), sizeBytes(), RTT_SHORT, cg.null());
}

std::string LgsShort::getName() {
    return name;
}

LgsExpr* LgsShort::getZeroValue() {
    return new LgsIntConst(&LGS_SHORT, 0);
}

bool LgsShort::canCastTo(LgsType* other) {
    const auto IRName = other->getName();
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsInt::name) return true;
    if (IRName == LgsUInt::name) return true;
    if (IRName == LgsSize::name) return true;
    if (IRName == LgsLong::name) return true;
    if (IRName == LgsFloat::name) return true;
    return name == IRName;
}

std::string LgsShort::strFormatPart() const {
    return "%d";
}

llvm::DIType* LgsShort::getDebugType(LgsCgModule& cg) {
    assert(0);
}