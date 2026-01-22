#include "codegen/LgsCgModule.h"
#include "exprs/constants/LgsCharConst.h"
#include "types/LgsAny.h"
#include "types/iterables/LgsStr.h"
#include <llvm/IR/Module.h>


size_t LgsChar::sizeBytes() {
    return sizeof(char);
}

Type* LgsChar::getIRType(LgsCgModule& cg) {
    return cg.i8Ty();
}

Constant* LgsChar::getRTType(LgsCgModule& cg) {
    return cg.getRTTypeInfo(getName(), IRSize(cg), RTT_CHAR);
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
    assert(0);
}

bool LgsChar::canCastTo(LgsType* other) {
    const auto IRName = other->getName();
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsStr::name) return true;
    return name == IRName;
}

DIType* LgsChar::getDebugType(LgsCgModule& cg) {
    assert(0);
}