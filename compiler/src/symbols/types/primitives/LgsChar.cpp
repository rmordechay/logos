#include <string>

#include "codegen/LgsCodeGen.h"
#include "exprs/constants/LgsCharConst.h"
#include "types/primitives/LgsAny.h"
#include "types/iterables/LgsStr.h"
#include "LgsType.h"
#include "types/primitives/LgsChar.h"


size_t LgsChar::sizeBytes() {
    return sizeof(char);
}

Type* LgsChar::getIRType(LgsCodeGen& cg) {
    return cg.i8Ty();
}

std::string LgsChar::getName() {
    return name;
}

LgsExpr* LgsChar::getZeroValue() {
    return new LgsCharConst('0');
}

std::string LgsChar::fmtStr() const {
    return "'%c'";
}

LgsType* LgsChar::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    return nullptr;
}

bool LgsChar::canCastTo(LgsType* other) {
    const auto IRName = other->getName();
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsStr::name) return true;
    return name == IRName;
}

DIType* LgsChar::getDebugType(LgsCodeGen& cg) {
    assert(0);
}