#include "codegen/LgsLLVMGen.h"
#include "exprs/constants/LgsCharConst.h"
#include "types/LgsAny.h"
#include "types/iterables/LgsStr.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsLong.h"
#include "types/primitives/LgsShort.h"
#include "types/primitives/LgsSize.h"
#include "types/primitives/LgsUInt.h"


size_t LgsChar::getSizeBytes() {
    return sizeof(char);
}

Type* LgsChar::getIRType(LgsLLVMGen& cg) {
    return cg.i8Ty();
}

std::string LgsChar::getName() {
    return name;
}

LgsExpr* LgsChar::getZeroValue() {
    return new LgsCharConst('0');
}

Lgs_TypeKind LgsChar::getRTTypeKind() {
    return RTT_CHAR;
}

std::string LgsChar::strFormatPart() const {
    return "%c";
}

bool LgsChar::canCastTo(LgsType* other) {
    const auto IRName = other->getName();
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsStr::name) return true;
    if (IRName == LgsShort::name) return true;
    if (IRName == LgsInt::name) return true;
    if (IRName == LgsSize::name) return true;
    if (IRName == LgsLong::name) return true;
    if (IRName == LgsFloat::name) return true;
    if (IRName == LgsUInt::name) return true;
    return name == IRName;
}