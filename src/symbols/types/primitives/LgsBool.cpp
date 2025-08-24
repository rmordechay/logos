#include "types/primitives/LgsBool.h"
#include "exprs/unary/constants/LgsIntConst.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsLong.h"
#include "types/primitives/LgsShort.h"
#include "types/primitives/LgsSize.h"
#include "types/primitives/LgsUInt.h"

json::value LgsBool::asJSON() {
    json::object obj;
    obj["name"] = name;
    return obj;
}

std::string LgsBool::pname() {
    return name;
}

Type* LgsBool::getIRType(LgsLLVM& codeGen) {
    return codeGen.i1Ty();
}

std::string LgsBool::getName() {
    return name;
}

LgsExpr* LgsBool::getZeroValue() {
    return new LgsIntConst(&LGS_BOOL, false);
}

bool LgsBool::canCastTo(LgsType* other) {
    const auto IRName = other->getName();
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsShort::name) return true;
    if (IRName == LgsInt::name) return true;
    if (IRName == LgsUInt::name) return true;
    if (IRName == LgsSize::name) return true;
    if (IRName == LgsLong::name) return true;
    if (IRName == LgsFloat::name) return true;
    return name == IRName;
}

std::string LgsBool::strFormatPart() const {
    return "%d";
}

size_t LgsBool::getSizeBytes() {
    return sizeof(bool);
}
