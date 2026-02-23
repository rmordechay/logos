#include "types/primitives/LgsByte.h"

#include <assert.h>

#include "codegen/LgsCodeGen.h"
#include "exprs/constants/LgsIntConst.h"
#include "types/primitives/LgsAny.h"
#include "types/primitives/LgsChar.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsLong.h"
#include "types/primitives/LgsShort.h"
#include "types/primitives/LgsSize.h"
#include "types/primitives/LgsUInt.h"

Type* LgsByte::getIRType(LgsCodeGen& cg) {
    return cg.i8Ty();
}

LgsType* LgsByte::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    return nullptr;
}

size_t LgsByte::sizeBytes() {
    return sizeof(int8_t);
}

LgsExpr* LgsByte::getZeroValue() {
    return new LgsIntConst(&LGS_BYTE, false);
}

std::string LgsByte::getName() {
    return name;
}

bool LgsByte::canCastTo(LgsType* other) {
    const auto IRName = other->getName();
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsChar::name) return true;
    if (IRName == LgsShort::name) return true;
    if (IRName == LgsInt::name) return true;
    if (IRName == LgsSize::name) return true;
    if (IRName == LgsLong::name) return true;
    if (IRName == LgsFloat::name) return true;
    if (IRName == LgsUInt::name) return true;
    return name == IRName;
}

std::string LgsByte::fmtStr() const {
    return "%d";
}

DIType* LgsByte::getDebugType(LgsCodeGen& cg) {
    assert(0);
}