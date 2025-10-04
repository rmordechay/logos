#include "types/primitives/LgsInt.h"
#include "exprs/constants/LgsIntConst.h"
#include "stmts/LgsField.h"
#include "types/LgsAny.h"
#include "types/LgsPtr.h"
#include "types/primitives/LgsDouble.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsSize.h"
#include <llvm/IR/DIBuilder.h>

size_t LgsInt::getSizeBytes() {
    return sizeof(int);
}

Type* LgsInt::getIRType(LgsLLVMGen& cg) {
    return cg.i32Ty();
}

LgsExpr* LgsInt::getZeroValue() {
    return new LgsIntConst(&LGS_INT, 0);
}

Lgs_RTType LgsInt::getRTType() {
    return RTT_INT;
}

bool LgsInt::canCastTo(LgsType* other) {
    const auto otherName = other->getName();
    if (name == otherName) return true;
    if (otherName == LgsAny::name) return true;
    if (otherName == LgsSize::name) return true;
    if (otherName == LgsLong::name) return true;
    if (otherName == LgsFloat::name) return true;
    if (otherName == LgsDouble::name) return true;
    return false;
}

LgsType* LgsInt::applyOp(const LgsOperator op, LgsType* other) {
    if (op == DIV) {
        return &LGS_FLOAT;
    }
    if (other->asFloat()) {
        return &LGS_FLOAT;
    }
    if (other->asDouble()) {
        assert(0);
    }
    const auto IRName = other->getName();
    if (name == IRName) return this;
    return nullptr;
}

Value* LgsInt::addIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto l = cg.builder.CreateZExt(self, cg.i64Ty());
    const auto r = cg.builder.CreateZExt(other, cg.i64Ty());
    return cg.builder.CreateAdd(l, r);
}

Value* LgsInt::subIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto l = cg.builder.CreateZExt(self, getIRType(cg));
    const auto r = cg.builder.CreateZExt(other, getIRType(cg));
    return cg.builder.CreateSub(l, r);
}

Value* LgsInt::mulIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto l = cg.builder.CreateZExt(self, getIRType(cg));
    const auto r = cg.builder.CreateZExt(other, getIRType(cg));
    return cg.builder.CreateMul(l, r);
}

Value* LgsInt::divIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto l = cg.builder.CreateZExt(self, getIRType(cg));
    const auto r = cg.builder.CreateZExt(other, getIRType(cg));
    return cg.builder.CreateSDiv(l, r);
}

Value* LgsInt::modIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateSRem(self, other);
}

Value* LgsInt::bitAndIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateAnd(self, other);
}

Value* LgsInt::bitOrIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateOr(self, other);
}

Value* LgsInt::bitXorIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateXor(self, other);
}

Value* LgsInt::rshiftIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateShl(self, other);
}

Value* LgsInt::lshiftIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateLShr(self, other);
}

std::string LgsInt::strFormatPart() const {
    return "%d";
}

std::string LgsInt::getName() {
    return name;
}

json::value LgsInt::asJsonStr() {
    json::object jsonObj;
    jsonObj["name"] = name;
    return jsonObj;
}

DIBasicType* LgsInt::getDebugType(LgsLLVMGen& cg) {
    return cg.diBuilder->createBasicType(name, 32, dwarf::DW_ATE_signed);
}
