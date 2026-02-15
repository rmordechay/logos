#include "types/primitives/LgsBool.h"
#include <llvm/IR/Module.h>
#include "exprs/constants/LgsIntConst.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsChar.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsLong.h"
#include "types/primitives/LgsShort.h"
#include "types/primitives/LgsSize.h"
#include "types/primitives/LgsUInt.h"

Type* LgsBool::getIRType(LgsCodeGen& cg) {
    return cg.i1Ty();
}

LgsType* LgsBool::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    return nullptr;
}

void LgsBool::getAsIRText(LgsCodeGen& cg, LgsStrBuilder& strBuilder, Value* ptr) {
    const auto trueStr = cg.getString(trueLiteral, false);
    const auto falseStr = cg.getString(falseLiteral, false);
    const auto v = cg.builder.CreateSelect(cg.load(getIRType(cg), ptr), trueStr, falseStr);
    strBuilder.add(cg, v, cg.callStrlen(v));
}

Value* LgsBool::getIRZeroValue(LgsCodeGen& cg, Value* pointee) {
    return cg.false_();
}

std::string LgsBool::getName() {
    return name;
}

LgsExpr* LgsBool::getZeroValue() {
    return new LgsIntConst(&LGS_BOOL, false);
}

std::string LgsBool::fmtStr() const {
    return "%s";
}

size_t LgsBool::sizeBytes() {
    return sizeof(bool);
}

bool LgsBool::canCastTo(LgsType* other) {
    const auto otherName = other->getName();
    if (other->isAny()) return true;
    if (otherName == LgsChar::name) return true;
    if (otherName == LgsShort::name) return true;
    if (otherName == LgsInt::name) return true;
    if (otherName == LgsSize::name) return true;
    if (otherName == LgsLong::name) return true;
    if (otherName == LgsFloat::name) return true;
    if (otherName == LgsUInt::name) return true;
    return name == otherName;
}

DIType* LgsBool::getDebugType(LgsCodeGen& cg) {
    assert(0);
}