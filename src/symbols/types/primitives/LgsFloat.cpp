#include "types/primitives/LgsFloat.h"
#include "codegen/LgsLLVMGen.h"
#include "exprs/constants/LgsFloatConst.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsDouble.h"

std::pair<Value*, Value*> loadOperands(LgsLLVMGen& cg, Value* self, Value* other) {
    auto l = self;
    auto r = other;
    if (l->getType()->isIntegerTy()) {
        l = cg.builder.CreateSIToFP(l, cg.floatTy());
    }
    if (r->getType()->isIntegerTy()) {
        r = cg.builder.CreateSIToFP(r, cg.floatTy());
    }
    return {l, r};
}

json::value LgsFloat::asJsonStr() {
    assert(0);
}

std::string LgsFloat::pname() {
    return name;
}

Type* LgsFloat::getIRType(LgsLLVMGen& cg) {
    return Type::getFloatTy(cg.context);
}

std::string LgsFloat::getName() {
    return name;
}

LgsExpr* LgsFloat::getZeroValue() {
    return new LgsFloatConst(this, 0.0);
}

Lgs_RTType LgsFloat::getRTType() {
    return RTT_FLOAT;
}

size_t LgsFloat::getSizeBytes() {
    return sizeof(float);
}

std::string LgsFloat::strFormatPart() const {
    return "%.3f";
}

bool LgsFloat::canCastTo(LgsType* other) {
    const auto IRName = other->getName();
    if (name == IRName) return true;
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsDouble::name) return true;
    return false;
}

LgsType* LgsFloat::applyOp(LgsType* other, const LgsOperator op) {
    if (other->asInt()) return this;
    const auto IRName = other->getName();
    if (name == IRName) return this;
    return nullptr;
}

Value* LgsFloat::addIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto [l, r] = loadOperands(cg, self, other);
    return cg.builder.CreateFAdd(l, r);
}

Value* LgsFloat::subIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto [l, r] = loadOperands(cg, self, other);
    return cg.builder.CreateFSub(l, r);
}

Value* LgsFloat::mulIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto [l, r] = loadOperands(cg, self, other);
    return cg.builder.CreateFMul(l, r);
}

Value* LgsFloat::divIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto [l, r] = loadOperands(cg, self, other);
    return cg.builder.CreateFDiv(l, r);
}

Value* LgsFloat::eqIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto [l, r] = loadOperands(cg, self, other);
    return cg.builder.CreateFCmpOEQ(l, r);
}
