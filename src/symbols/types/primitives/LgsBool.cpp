#include "types/primitives/LgsBool.h"
#include "exprs/constants/LgsIntConst.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsLong.h"
#include "types/primitives/LgsShort.h"
#include "types/primitives/LgsSize.h"
#include "types/primitives/LgsUInt.h"

json::value LgsBool::asJSON() {
    json::object obj;
    obj["name"] = name;
    return obj;
}

std::string LgsBool::pname() {
    return name;
}

Type* LgsBool::getIRType(LgsLLVMGen& cg) {
    return cg.i1Ty();
}

Value* LgsBool::addIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    auto [l, r] = self->loadOperands(cg, other);
    return cg.builder.CreateAdd(l, r);
}

Value* LgsBool::subIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    auto [l, r] = self->loadOperands(cg, other);
    return cg.builder.CreateSub(l, r);
}

Value* LgsBool::mulIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    auto [l, r] = self->loadOperands(cg, other);
    return cg.builder.CreateMul(l, r);
}

Value* LgsBool::divIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    auto [l, r] = self->loadOperands(cg, other);
    return cg.builder.CreateUDiv(l, r);
}

Value* LgsBool::modIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    auto [l, r] = self->loadOperands(cg, other);
    return cg.builder.CreateSRem(l, r);
}

Value* LgsBool::eqIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    auto [l, r] = self->loadOperands(cg, other);
    return cg.builder.CreateICmpEQ(l, r);
}

Value* LgsBool::neIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    auto [l, r] = self->loadOperands(cg, other);
    return cg.builder.CreateICmpNE(l, r);
}

Value* LgsBool::ltIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    auto [l, r] = self->loadOperands(cg, other);
    return cg.builder.CreateICmpSLT(l, r);
}

Value* LgsBool::gtIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    auto [l, r] = self->loadOperands(cg, other);
    return cg.builder.CreateICmpSGT(l, r);
}

Value* LgsBool::geIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    auto [l, r] = self->loadOperands(cg, other);
    return cg.builder.CreateICmpSGE(l, r);
}

Value* LgsBool::leIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    auto [l, r] = self->loadOperands(cg, other);
    return cg.builder.CreateICmpSLE(l, r);
}

std::string LgsBool::getName() {
    return name;
}

LgsExpr* LgsBool::getZeroValue() {
    return new LgsIntConst(&LGS_BOOL, false);
}

bool LgsBool::canCastTo(LgsType* other) {
    const auto IRName = other->getName();
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsShort::name) return true;
    if (IRName == LgsBool::name) return true;
    if (IRName == LgsUInt::name) return true;
    if (IRName == LgsSize::name) return true;
    if (IRName == LgsLong::name) return true;
    if (IRName == LgsFloat::name) return true;
    return name == IRName;
}

std::string LgsBool::strFormatPart() const {
    return "%d";
}

size_t LgsBool::getSizeBytes() {
    return sizeof(bool);
}
