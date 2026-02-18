#include "types/primitives/LgsShort.h"

#include <llvm/IR/Module.h>

#include "exprs/constants/LgsIntConst.h"
#include "types/primitives/LgsAny.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsLong.h"
#include "types/primitives/LgsSize.h"
#include "types/primitives/LgsUInt.h"

size_t LgsShort::sizeBytes() {
    return sizeof(short);
}

Type* LgsShort::getIRType(LgsCodeGen& cg) {
    return cg.i16Ty();
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

LgsType* LgsShort::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    return nullptr;
}

std::string LgsShort::fmtStr() const {
    return "%d";
}

DIType* LgsShort::getDebugType(LgsCodeGen& cg) {
    assert(0);
}