#include "types/primitives/LgsLong.h"
#include "exprs/constants/LgsIntConst.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsChar.h"
#include "types/primitives/LgsDouble.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsShort.h"
#include "types/primitives/LgsSize.h"

json::value LgsLong::asJsonStr() {
    assert(0);
}

Type* LgsLong::getIRType(LgsLLVMGen& cg) {
    return cg.i64Ty();
}

size_t LgsLong::getSizeBytes() {
    return sizeof(long);
}

LgsExpr* LgsLong::getZeroValue() {
    return new LgsIntConst(&LGS_LONG, 0);
}

Lgs_RTType LgsLong::getRTType() {
    return RTT_LONG;
}

LgsType* LgsLong::applyOp(const LgsOperator op, LgsType* other) {
    if (op == DIV) {
        return &LGS_DOUBLE;
    }
    if (other->asFloat()) {
        return &LGS_DOUBLE;
    }
    if (other->asDouble()) {
        assert(0);
    }
    const auto IRName = other->getName();
    if (name == IRName) return this;
    return nullptr;
}

Value* LgsLong::addIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto l = cg.builder.CreateZExt(self, getIRType(cg));
    const auto r = cg.builder.CreateZExt(other, getIRType(cg));
    return cg.builder.CreateAdd(l, r);
}

Value* LgsLong::subIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto l = cg.builder.CreateZExt(self, getIRType(cg));
    const auto r = cg.builder.CreateZExt(other, getIRType(cg));
    return cg.builder.CreateSub(l, r);
}

Value* LgsLong::mulIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto l = cg.builder.CreateZExt(self, getIRType(cg));
    const auto r = cg.builder.CreateZExt(other, getIRType(cg));
    return cg.builder.CreateMul(l, r);
}

Value* LgsLong::divIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto l = cg.builder.CreateZExt(self, getIRType(cg));
    const auto r = cg.builder.CreateZExt(other, getIRType(cg));
    return cg.builder.CreateSDiv(l, r);
}

Value* LgsLong::modIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateSRem(self, other);
}

Value* LgsLong::bitAndIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateAnd(self, other);
}

Value* LgsLong::bitOrIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateOr(self, other);
}

Value* LgsLong::bitXorIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateXor(self, other);
}

Value* LgsLong::rshiftIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateShl(self, other);
}

Value* LgsLong::lshiftIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateLShr(self, other);
}

std::string LgsLong::getName() {
    return name;
}

bool LgsLong::canCastTo(LgsType* other) {
    const auto otherName = other->getName();
    if (otherName == LgsAny::name) return true;
    if (otherName == LgsChar::name) return true;
    if (otherName == LgsBool::name) return true;
    if (otherName == LgsShort::name) return true;
    if (otherName == LgsInt::name) return true;
    if (otherName == LgsSize::name) return true;
    if (otherName == LgsFloat::name) return true;
    return name == otherName;
}

std::string LgsLong::strFormatPart() const {
    return "%lu";
}
