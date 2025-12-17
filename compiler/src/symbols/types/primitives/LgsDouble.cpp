#include "types/primitives/LgsDouble.h"
#include "exprs/constants/LgsFloatConst.h"
#include "codegen/LgsCgModule.h"
#include "types/LgsAny.h"

std::string LgsDouble::getName() {
    return name;
}

size_t LgsDouble::sizeBytes() {
    return sizeof(double_t);
}

LgsExpr* LgsDouble::getZeroValue() {
    return new LgsFloatConst(this, 0.0);
}

LgsType* LgsDouble::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    assert(0);
}

std::string LgsDouble::fmtStr() const {
    return "%f";
}

Type* LgsDouble::getIRType(LgsCgModule& cg) {
    return cg.builder.getDoubleTy();
}

Constant* LgsDouble::getRTType(LgsCgModule& cg) {
    return cg.getRTTypeInfo(getName(), sizeBytes(), RTT_DOUBLE, isHeapAlloc, cg.null());
}

bool LgsDouble::canCastTo(LgsType* other) {
    const auto IRName = other->getName();
    if (name == IRName) return true;
    if (other->asGenericType()) return true;
    if (IRName == LgsAny::name) return true;
    return false;
}

Value* LgsDouble::addIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto [l, r] = loadPairAsDouble(cg, left, right);
    return cg.builder.CreateFAdd(l, r);
}

Value* LgsDouble::mulIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto [l, r] = loadPairAsDouble(cg, left, right);
    return cg.builder.CreateFMul(l, r);
}

Value* LgsDouble::powIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto [l, r] = loadPairAsDouble(cg, left, right);
    return cg.callFunc("pow", cg.doubleTy(), {cg.doubleTy(), cg.doubleTy()}, {l, r});
}

DIType* LgsDouble::getDebugType(LgsCgModule& cg) {
    assert(0);
}