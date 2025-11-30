#include "types/primitives/LgsULong.h"
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
    return cg.getRTTypeInfo(getGenericName(), sizeBytes(), sizeBytes(), RTT_ULONG, cg.null());
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

LgsType* LgsULong::applyBinOp(LgsType* toType, LgsBinOp& op) {
    assert(0);
}

DIType* LgsULong::getDebugType(LgsCgModule& cg) {
    assert(0);
}

std::string LgsULong::strFormatPart() const {
    return "%ul";
}