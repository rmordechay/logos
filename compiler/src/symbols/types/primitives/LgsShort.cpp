#include "types/primitives/LgsShort.h"

#include <assert.h>

#include "exprs/constants/LgsIntConst.h"
#include "types/primitives/LgsAny.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsLong.h"
#include "types/primitives/LgsSize.h"
#include "types/primitives/LgsUInt.h"
#include "codegen/LgsCodeGen.h"

size_t LgsShort::sizeBytes() {
    return sizeof(short);
}

Type* LgsShort::getIRType(LgsCodeGen& cg) {
    return cg.i16Ty();
}

void LgsShort::asIRText(LgsStrBuilder& sb, Value* value) {
    const auto buffer = sb.cg.emptyBuffer(128);
    const auto bytesRead = sb.cg.callSnprintf(fmtStr(), buffer, sb.cg.usize(128), sb.cg.toInt(value));
    sb.add(buffer, sb.cg.toSize(bytesRead));
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

Value* LgsShort::getIRZeroValue(LgsCodeGen& cg, Value* pointee, Value* level) {
    return cg.zero16();
}

Value* LgsShort::hashValue(LgsCodeGen& cg, Value* value) {
    return value;
}

DIType* LgsShort::getDebugType(LgsCodeGen& cg) {
    assert(0);
}
