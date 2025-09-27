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

Value* LgsInt::addIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto l = cg.builder.CreateZExt(self, getIRType(cg));
    const auto r = cg.builder.CreateZExt(other, getIRType(cg));
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

Value* LgsInt::eqIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateICmpEQ(self, other);
}

Value* LgsInt::neIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateICmpNE(self, other);
}

Value* LgsInt::ltIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateICmpSLT(self, other);
}

Value* LgsInt::gtIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateICmpSGT(self, other);
}

Value* LgsInt::geIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateICmpSGE(self, other);
}

Value* LgsInt::leIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateICmpSLE(self, other);
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

Value* LgsInt::andIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto currentBlock = cg.builder.GetInsertBlock();
    const auto func = currentBlock->getParent();
    const auto rightBlock = cg.createBlock("and_right", func);
    const auto endBlock = cg.createBlock("and_end", func);
    cg.builder.CreateCondBr(other, rightBlock, endBlock);
    cg.builder.SetInsertPoint(rightBlock);
    cg.builder.CreateBr(endBlock);
    cg.builder.SetInsertPoint(endBlock);
    auto* phi = cg.builder.CreatePHI(cg.builder.getInt1Ty(), 2);
    phi->addIncoming(cg.false_(), currentBlock);
    phi->addIncoming(other, rightBlock);
    return phi;
}

Value* LgsInt::orIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto currentBlock = cg.builder.GetInsertBlock();
    const auto func = currentBlock->getParent();
    const auto rightBlock = cg.createBlock("or_right", func);
    const auto endBlock = cg.createBlock("or_end", func);
    cg.builder.CreateCondBr(self, endBlock, rightBlock);
    cg.builder.SetInsertPoint(rightBlock);
    cg.builder.CreateBr(endBlock);
    cg.builder.SetInsertPoint(endBlock);
    auto* phi = cg.builder.CreatePHI(cg.builder.getInt1Ty(), 2);
    phi->addIncoming(cg.true_(), currentBlock);
    phi->addIncoming(other, rightBlock);
    return phi;
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

json::value LgsInt::asJsonStr() {
    json::object jsonObj;
    jsonObj["name"] = name;
    return jsonObj;
}

DIBasicType* LgsInt::getDebugType(LgsLLVMGen& cg) {
    return cg.diBuilder->createBasicType(name, 32, dwarf::DW_ATE_signed);
}
