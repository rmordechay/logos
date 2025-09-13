#include "types/primitives/LgsFloat.h"
#include "codegen/LgsLLVMGen.h"
#include "exprs/LgsNull.h"
#include "exprs/constants/LgsFloatConst.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsDouble.h"

json::value LgsFloat::asJSON() {
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

Value* LgsFloat::addIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
        auto l = self->loadIR(cg);
    auto r = other->loadIR(cg);
    if (l->getType()->isIntegerTy()) {
        l = cg.builder.CreateSIToFP(l, cg.floatTy());
    }
    if (r->getType()->isIntegerTy()) {
        r = cg.builder.CreateSIToFP(r, cg.floatTy());
    }
    return cg.builder.CreateFAdd(l, r);
}

Value* LgsFloat::subIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
        auto l = self->loadIR(cg);
    auto r = other->loadIR(cg);
    if (l->getType()->isIntegerTy()) {
        l = cg.builder.CreateSIToFP(l, cg.floatTy());
    }
    if (r->getType()->isIntegerTy()) {
        r = cg.builder.CreateSIToFP(r, cg.floatTy());
    }
    return cg.builder.CreateFSub(l, r);
}

Value* LgsFloat::mulIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
        auto l = self->loadIR(cg);
    auto r = other->loadIR(cg);
    if (l->getType()->isIntegerTy()) {
        l = cg.builder.CreateSIToFP(l, cg.floatTy());
    }
    if (r->getType()->isIntegerTy()) {
        r = cg.builder.CreateSIToFP(r, cg.floatTy());
    }
    return cg.builder.CreateFMul(l, r);
}

Value* LgsFloat::divIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    auto l = self->loadIR(cg);
    auto r = other->loadIR(cg);
    if (l->getType()->isIntegerTy()) {
        l = cg.builder.CreateSIToFP(l, cg.floatTy());
    }
    if (r->getType()->isIntegerTy()) {
        r = cg.builder.CreateSIToFP(r, cg.floatTy());
    }
    return cg.builder.CreateFDiv(l, r);
}
