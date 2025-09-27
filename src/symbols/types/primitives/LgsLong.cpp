#include "types/primitives/LgsLong.h"
#include "exprs/constants/LgsIntConst.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsChar.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsShort.h"
#include "types/primitives/LgsSize.h"

json::value LgsLong::asJsonStr() {
    assert(0);
}

std::string LgsLong::pname() {
    return name;
}

Type* LgsLong::getIRType(LgsLLVMGen& cg) {
    return cg.i64Ty();
}

size_t LgsLong::getSizeBytes() {
    return sizeof(long);
}

LgsExpr* LgsLong::getZeroValue() {
    return new LgsIntConst(&LGS_LONG, 0);
}

Lgs_RTType LgsLong::getRTType() {
    return RTT_LONG;
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

std::string LgsLong::strFormatPart() const {
    return "%lu";
}
