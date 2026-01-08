#include "codegen/LgsCgModule.h"
#include "exprs/constants/LgsCharConst.h"
#include "types/LgsAny.h"
#include "types/iterables/LgsStr.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsLong.h"
#include "types/primitives/LgsShort.h"
#include "types/primitives/LgsSize.h"
#include "types/primitives/LgsUInt.h"


size_t LgsChar::sizeBytes() {
    return sizeof(char);
}

Type* LgsChar::getIRType(LgsCgModule& cg) {
    return cg.i8Ty();
}

Constant* LgsChar::getRTType(LgsCgModule& cg) {
    return cg.getRTTypeInfo(getName(), sizeBytes(), RTT_CHAR, cg.null());
}

std::string LgsChar::getName() {
    return name;
}

LgsExpr* LgsChar::getZeroValue() {
    return new LgsCharConst('0');
}

std::string LgsChar::fmtStr() const {
    return "%c";
}

LgsType* LgsChar::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    assert(0);
}

bool LgsChar::canCastTo(LgsType* other) {
    const auto IRName = other->getName();
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsShort::name) return true;
    if (IRName == LgsInt::name) return true;
    if (IRName == LgsSize::name) return true;
    if (IRName == LgsLong::name) return true;
    if (IRName == LgsFloat::name) return true;
    if (IRName == LgsUInt::name) return true;
    return name == IRName;
}

DIType* LgsChar::getDebugType(LgsCgModule& cg) {
    assert(0);
}