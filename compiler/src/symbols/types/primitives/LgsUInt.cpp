#include "types/primitives/LgsUInt.h"

#include <llvm/IR/Module.h>

#include "exprs/constants/LgsIntConst.h"
#include "codegen/LgsCodeGen.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsSize.h"

size_t LgsUInt::sizeBytes() {
    return sizeof(uint32_t);
}

Type* LgsUInt::getIRType(LgsCodeGen& cg) {
    return cg.i32Ty();
}

Constant* LgsUInt::getRTType(LgsCodeGen& cg) {
    return cg.getRTTypeInfo(getName(), IRSize(cg), RTT_UINT);
}

std::string LgsUInt::getName() {
    return name;
}

LgsExpr* LgsUInt::getZeroValue() {
    return new LgsIntConst(this, 0);
}

bool LgsUInt::canCastTo(LgsType* other) {
    const auto IRName = other->getName();
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsInt::name) return true;
    if (IRName == LgsSize::name) return true;
    return name == IRName;
}

LgsType* LgsUInt::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    assert(0);
}

DIType* LgsUInt::getDebugType(LgsCodeGen& cg) {
    assert(0);
}

std::string LgsUInt::fmtStr() const {
    return "%d";
}
