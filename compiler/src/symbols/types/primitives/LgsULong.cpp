#include "types/primitives/LgsULong.h"
#include "exprs/constants/LgsIntConst.h"
#include "codegen/LgsLLVMGen.h"
#include "types/LgsAny.h"

size_t LgsULong::sizeBytes() {
    return sizeof(uint64_t);
}

Type* LgsULong::getIRType(LgsLLVMGen& cg) {
    return cg.i32Ty();
}

Constant* LgsULong::getRTType(LgsLLVMGen& cg) {
    return cg.getRTTypeInfo(getGenericName(), sizeBytes(), RTT_ULONG, cg.null());
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

llvm::DIType* LgsULong::getDebugType(LgsLLVMGen& cg) {
    assert(0);
}

std::string LgsULong::strFormatPart() const {
    return "%ul";
}

LgsType* LgsULong::clone() {
    return this;
}
