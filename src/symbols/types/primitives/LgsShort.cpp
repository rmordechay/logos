#include "exprs/unary/constants/LgsShortConst.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsLong.h"
#include "types/primitives/LgsSize.h"
#include "types/primitives/LgsUInt.h"


size_t LgsShort::getSizeBytes() {
    return sizeof(short);
}

Type* LgsShort::getIRType(LgsCodeGen* codeGen) {
    return codeGen->i16Ty();
}

string LgsShort::prettyName() {
    return name;
}

string LgsShort::getName() {
    return name;
}

LgsExpr* LgsShort::getZeroValue() {
    return new LgsShortConst(0);
}

bool LgsShort::equals(LgsType* other) {
    const auto IRName = other->getName();
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsInt::name) return true;
    if (IRName == LgsUInt::name) return true;
    if (IRName == LgsSize::name) return true;
    if (IRName == LgsLong::name) return true;
    if (IRName == LgsFloat::name) return true;
    return name == IRName;
}

string LgsShort::strFormatPart() const {
    return "%d";
}