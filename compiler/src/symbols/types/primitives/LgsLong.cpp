#include "types/primitives/LgsLong.h"
#include <assert.h>
#include "exprs/constants/LgsIntConst.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsChar.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsShort.h"
#include "types/primitives/LgsSize.h"

Type* LgsLong::getIRType(LgsCodeGen& cg) {
    return cg.i64Ty();
}

size_t LgsLong::sizeBytes() {
    return sizeof(long);
}

LgsExpr* LgsLong::getZeroValue() {
    return new LgsIntConst(&LGS_LONG, 0);
}

LgsType* LgsLong::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    return nullptr;
}

void LgsLong::asIRText(LgsStrBuilder& sb, Value* value) {
    const auto buffer = sb.cg.emptyBuffer(25);
    const auto bytesRead = sb.cg.callSnprintf(fmtStr(), buffer, sb.cg.usize(25), sb.cg.toLong(value));
    sb.add(buffer, sb.cg.toSize(bytesRead));
}

std::string LgsLong::getName() {
    return name;
}

bool LgsLong::canCastTo(LgsType* other) {
    const auto otherName = other->getName();
    if (other->isAny()) return true;
    if (otherName == LgsChar::name) return true;
    if (otherName == LgsBool::name) return true;
    if (otherName == LgsShort::name) return true;
    if (otherName == LgsInt::name) return true;
    if (otherName == LgsSize::name) return true;
    if (otherName == LgsFloat::name) return true;
    return name == otherName;
}

DIType* LgsLong::getDebugType(LgsCodeGen& cg) {
    assert(0);
}

std::string LgsLong::fmtStr() const {
    return "%" PRId64;
}
