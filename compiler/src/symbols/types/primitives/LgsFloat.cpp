#include "types/primitives/LgsFloat.h"
#include "codegen/LgsCgModule.h"
#include "exprs/constants/LgsFloatConst.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsDouble.h"

std::string LgsFloat::getName() {
    return name;
}

Type* LgsFloat::getIRType(LgsCgModule& cg) {
    return Type::getFloatTy(cg.context);
}

LgsExpr* LgsFloat::getZeroValue() {
    return new LgsFloatConst(this, 0.0);
}

Constant* LgsFloat::getRTType(LgsCgModule& cg) {
    return cg.getRTTypeInfo(getGenericName(), sizeBytes(), sizeBytes(), RTT_FLOAT, cg.null());
}

size_t LgsFloat::sizeBytes() {
    return sizeof(float);
}

std::string LgsFloat::fmtStr() const {
    return "%.3f";
}

bool LgsFloat::canCastTo(LgsType* other) {
    const auto IRName = other->getName();
    if (name == IRName) return true;
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsDouble::name) return true;
    return false;
}

LgsType* LgsFloat::applyBinOp(LgsType* toType, LgsBinOp& op) {
    assert(0);
}

Value* LgsFloat::addIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto [l, r] = loadPairAsFloat(cg, left, right);
    return cg.builder.CreateFAdd(l, r);
}

Value* LgsFloat::subIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto [l, r] = loadPairAsFloat(cg, left, right);
    return cg.builder.CreateFSub(l, r);
}

Value* LgsFloat::mulIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    if (left->type->asVec() && right->type->asVec()) {
        return dotProduct(cg, left, right);
    }
    const auto [l, r] = loadPairAsFloat(cg, left, right);
    return cg.builder.CreateFMul(l, r);
}

Value* LgsFloat::divIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto [l, r] = loadPairAsFloat(cg, left, right);
    return cg.builder.CreateFDiv(l, r);
}

DIType* LgsFloat::getDebugType(LgsCgModule& cg) {
    assert(0);
}