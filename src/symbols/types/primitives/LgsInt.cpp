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

bool LgsInt::canCastTo(LgsType* other) {
    const auto otherName = other->getName();
    if (name == otherName) return true;
    if (otherName == LgsAny::name) return true;
    if (otherName == LgsSize::name) return true;
    if (otherName == LgsFloat::name) return true;
    if (otherName == LgsDouble::name) return true;
    return false;
}

LgsType* LgsInt::applyOp(LgsType* other, const LgsOperator op) {
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

Value* LgsInt::addIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    auto [l, r] = self->loadOperands(cg, other);
    return cg.builder.CreateAdd(l, r);
}

Value* LgsInt::subIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    auto [l, r] = self->loadOperands(cg, other);
    return cg.builder.CreateSub(l, r);
}

Value* LgsInt::mulIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    auto [l, r] = self->loadOperands(cg, other);
    return cg.builder.CreateMul(l, r);
}

Value* LgsInt::divIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    auto [l, r] = self->loadOperands(cg, other);
    return cg.builder.CreateUDiv(l, r);
}

Value* LgsInt::inIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    assert(0);
}

Value* LgsInt::modIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    auto [l, r] = self->loadOperands(cg, other);
    return cg.builder.CreateSRem(l, r);
}

Value* LgsInt::eqIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    auto [l, r] = self->loadOperands(cg, other);
    return cg.builder.CreateICmpEQ(l, r);
}

Value* LgsInt::neIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    auto [l, r] = self->loadOperands(cg, other);
    return cg.builder.CreateICmpNE(l, r);
}

Value* LgsInt::ltIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    auto [l, r] = self->loadOperands(cg, other);
    return cg.builder.CreateICmpSLT(l, r);
}

Value* LgsInt::gtIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    auto [l, r] = self->loadOperands(cg, other);
    return cg.builder.CreateICmpSGT(l, r);
}

Value* LgsInt::geIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    auto [l, r] = self->loadOperands(cg, other);
    return cg.builder.CreateICmpSGE(l, r);
}

Value* LgsInt::leIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    auto [l, r] = self->loadOperands(cg, other);
    return cg.builder.CreateICmpSLE(l, r);
}

Value* LgsInt::andIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    assert(0);
}

Value* LgsInt::orIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    assert(0);
}

Value* LgsInt::bitAndIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    auto [l, r] = self->loadOperands(cg, other);
    return cg.builder.CreateAnd(l, r);
}

Value* LgsInt::bitOrIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    auto [l, r] = self->loadOperands(cg, other);
    return cg.builder.CreateOr(l, r);
}

Value* LgsInt::bitXorIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    auto [l, r] = self->loadOperands(cg, other);
    return cg.builder.CreateXor(l, r);
}

Value* LgsInt::lshiftIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    auto [l, r] = self->loadOperands(cg, other);
    return cg.builder.CreateShl(l, r);
}

Value* LgsInt::rshiftIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    auto [l, r] = self->loadOperands(cg, other);
    return cg.builder.CreateLShr(l, r);
}


std::string LgsInt::strFormatPart() const {
    return "%d";
}

std::string LgsInt::getName() {
    return name;
}

std::string LgsInt::pname() {
    return getName();
}

json::value LgsInt::asJSON() {
    json::object jsonObj;
    jsonObj["name"] = name;
    return jsonObj;
}

LgsType* LgsInt::clone() {
    return this;
}

DIBasicType* LgsInt::getDebugType(LgsLLVMGen& cg) {
    return cg.diBuilder->createBasicType(name, 32, dwarf::DW_ATE_signed);
}
