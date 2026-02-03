#include "types/primitives/LgsULong.h"

#include <llvm/IR/Module.h>

#include "exprs/constants/LgsIntConst.h"
#include "codegen/LgsCodeGen.h"
#include "types/LgsAny.h"

size_t LgsULong::sizeBytes() {
    return sizeof(uint64_t);
}

Type* LgsULong::getIRType(LgsCodeGen& cg) {
    return cg.i32Ty();
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
    return nullptr;
}

DIType* LgsULong::getDebugType(LgsCodeGen& cg) {
    assert(0);
}

std::string LgsULong::fmtStr() const {
    return "%ul";
}