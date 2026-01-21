#include "types/primitives/LgsLong.h"

#include <llvm/IR/Module.h>

#include "exprs/constants/LgsIntConst.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsChar.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsShort.h"
#include "types/primitives/LgsSize.h"

Type* LgsLong::getIRType(LgsCgModule& cg) {
    return cg.i64Ty();
}

Constant* LgsLong::getRTType(LgsCgModule& cg) {
    return cg.getRTTypeInfo(getName(), cg.getAllocSize(getIRType(cg)), RTT_LONG);
}

size_t LgsLong::sizeBytes() {
    return sizeof(long);
}

LgsExpr* LgsLong::getZeroValue() {
    return new LgsIntConst(&LGS_LONG, 0);
}

LgsType* LgsLong::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    assert(0);
}

std::string LgsLong::getName() {
    return name;
}

bool LgsLong::canCastTo(LgsType* other) {
    const auto otherName = other->getName();
    if (otherName == LgsAny::name) return true;
    if (otherName == LgsChar::name) return true;
    if (otherName == LgsBool::name) return true;
    if (otherName == LgsShort::name) return true;
    if (otherName == LgsInt::name) return true;
    if (otherName == LgsSize::name) return true;
    if (otherName == LgsFloat::name) return true;
    return name == otherName;
}

DIType* LgsLong::getDebugType(LgsCgModule& cg) {
    assert(0);
}

std::string LgsLong::fmtStr() const {
    return "%lu";
}
