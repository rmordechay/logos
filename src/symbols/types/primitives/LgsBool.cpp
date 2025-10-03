#include "types/primitives/LgsBool.h"
#include "exprs/constants/LgsIntConst.h"
#include "types/LgsAny.h"
#include "types/iterables/LgsIterable.h"
#include "types/primitives/LgsChar.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsLong.h"
#include "types/primitives/LgsShort.h"
#include "types/primitives/LgsSize.h"
#include "types/primitives/LgsUInt.h"

Type* LgsBool::getIRType(LgsLLVMGen& cg) {
    return cg.i1Ty();
}

LgsType* LgsBool::applyOp(const LgsOperator op, LgsType* other) {
    const auto IRName = other->getName();
    if (name != IRName) return nullptr;
    if (op == ADD) return extendInt();
    return this;
}

Value* LgsBool::addIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto l = cg.builder.CreateZExt(self, getIRType(cg));
    const auto r = cg.builder.CreateZExt(other, getIRType(cg));
    return cg.builder.CreateAdd(l, r);
}

Value* LgsBool::subIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto l = cg.builder.CreateZExt(self, getIRType(cg));
    const auto r = cg.builder.CreateZExt(other, getIRType(cg));
    return cg.builder.CreateSub(l, r);
}

Value* LgsBool::mulIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto l = cg.builder.CreateZExt(self, getIRType(cg));
    const auto r = cg.builder.CreateZExt(other, getIRType(cg));
    return cg.builder.CreateMul(l, r);
}

Value* LgsBool::divIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto l = cg.builder.CreateZExt(self, getIRType(cg));
    const auto r = cg.builder.CreateZExt(other, getIRType(cg));
    return cg.builder.CreateSDiv(l, r);
}

Value* LgsBool::modIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateSRem(self, other);
}

Value* LgsBool::bitAndIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateAnd(self, other);
}

Value* LgsBool::bitOrIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateOr(self, other);
}

Value* LgsBool::bitXorIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateXor(self, other);
}

Value* LgsBool::rshiftIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateShl(self, other);
}

Value* LgsBool::lshiftIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateLShr(self, other);
}

std::string LgsBool::getName() {
    return name;
}

json::value LgsBool::asJsonStr() {
    json::object obj;
    obj["name"] = name;
    return obj;
}

LgsExpr* LgsBool::getZeroValue() {
    return new LgsIntConst(&LGS_BOOL, false);
}

Lgs_RTType LgsBool::getRTType() {
    return RTT_BOOL;
}

std::string LgsBool::strFormatPart() const {
    return "%s";
}

size_t LgsBool::getSizeBytes() {
    return sizeof(bool);
}

bool LgsBool::canCastTo(LgsType* other) {
    const auto otherName = other->getName();
    if (otherName == LgsAny::name) return true;
    if (otherName == LgsChar::name) return true;
    if (otherName == LgsShort::name) return true;
    if (otherName == LgsInt::name) return true;
    if (otherName == LgsSize::name) return true;
    if (otherName == LgsLong::name) return true;
    if (otherName == LgsFloat::name) return true;
    if (otherName == LgsUInt::name) return true;
    return name == otherName;
}
