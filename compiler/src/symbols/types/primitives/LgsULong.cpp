#include "types/primitives/LgsULong.h"

#include <llvm/IR/Module.h>

#include "exprs/constants/LgsIntConst.h"
#include "codegen/LgsCgModule.h"
#include "types/LgsAny.h"

size_t LgsULong::sizeBytes() {
    return sizeof(uint64_t);
}

Type* LgsULong::getIRType(LgsCgModule& cg) {
    return cg.i32Ty();
}

Constant* LgsULong::getRTType(LgsCgModule& cg) {
    return cg.getRTTypeInfo(getName(), cg.getAllocSize(getIRType(cg)), RTT_ULONG);
}

std::string LgsULong::getName() {
    return name;
}

LgsExpr* LgsULong::getZeroValue() {
    return new LgsIntConst(this, 0);
}

bool LgsULong::canCastTo(LgsType* other) {
    const auto IRName = other->getName();
    if (IRName == LgsAny::name) return true;
    return name == IRName;
}

LgsType* LgsULong::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    assert(0);
}

DIType* LgsULong::getDebugType(LgsCgModule& cg) {
    assert(0);
}

std::string LgsULong::fmtStr() const {
    return "%ul";
}