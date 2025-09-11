#include "types/primitives/LgsInt.h"
#include "exprs/constants/LgsIntConst.h"
#include "stmts/LgsField.h"
#include "types/LgsAny.h"
#include "types/LgsPtr.h"
#include "types/primitives/LgsDouble.h"
#include "types/primitives/LgsFloat.h"
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
    if (otherName == LgsFloat::name) return true;
    if (otherName == LgsDouble::name) return true;
    return false;
}

bool LgsInt::canAssignTo(LgsType* other, const LgsAssignType op) {
    return canCastTo(other);
}

bool LgsInt::canApplyOp(LgsType* other, LgsOperator op) {
    const auto IRName = other->getName();
    if (name == IRName) return true;
    return false;
}

Value* LgsInt::addIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) {
    return cg.builder.CreateAdd(value, other->loadIR(cg));
}

Value* LgsInt::subIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) {
    return cg.builder.CreateSub(value, other->loadIR(cg));
}

Value* LgsInt::mulIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) {
    return cg.builder.CreateMul(value, other->loadIR(cg));
}

Value* LgsInt::divIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) {
    return cg.builder.CreateUDiv(value, other->loadIR(cg));
}

Value* LgsInt::inIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) {
    assert(0);
}

Value* LgsInt::modIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) {
    return cg.builder.CreateSRem(value, other->loadIR(cg));
}

Value* LgsInt::eqIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) {
    return cg.builder.CreateICmpEQ(value, other->loadIR(cg));
}

Value* LgsInt::neIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) {
    return cg.builder.CreateICmpNE(value, other->loadIR(cg));
}

Value* LgsInt::ltIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) {
    return cg.builder.CreateICmpSLT(value, other->loadIR(cg));
}

Value* LgsInt::gtIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) {
    return cg.builder.CreateICmpSGT(value, other->loadIR(cg));
}

Value* LgsInt::geIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) {
    return cg.builder.CreateICmpSGE(value, other->loadIR(cg));
}

Value* LgsInt::leIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) {
    return cg.builder.CreateICmpSLE(value, other->loadIR(cg));
}

Value* LgsInt::andIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) {
    assert(0);
}

Value* LgsInt::orIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) {
    assert(0);
}

Value* LgsInt::bitAndIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) {
    return cg.builder.CreateAnd(value, other->loadIR(cg));
}

Value* LgsInt::bitOrIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) {
    return cg.builder.CreateOr(value, other->loadIR(cg));
}

Value* LgsInt::bitXorIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) {
    return cg.builder.CreateXor(value, other->loadIR(cg));
}

Value* LgsInt::lshiftIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) {
    return cg.builder.CreateShl(value, other->loadIR(cg));
}

Value* LgsInt::rshiftIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) {
    return cg.builder.CreateLShr(value, other->loadIR(cg));
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
