#include "exprs/unary/constants/LgsUIntConst.h"
#include "exprs/unary/constants/LgsFloatConst.h"
#include "exprs/unary/constants/LgsLongConst.h"
#include "exprs/unary/constants/LgsStrConst.h"

string LgsUIntConst::prettyName() {
    return to_string(value);
}

Value* LgsUIntConst::createIRValue(LgsModule* runtime) {
    return runtime->builder.getInt32(value);
}

LgsExpr* LgsUIntConst::convertExpr(LgsType* toType) {
    if (toType->asUInt()) {
        return this;
    }
    if (toType->asStr()) {
        return new LgsStrConst(to_string(value));
    }
    if (toType->asLong()) {
        return new LgsLongConst(value);
    }
    assert(0);
}

LgsExpr* LgsUIntConst::clone() {
    return new LgsIntConst(value);
}

Value* LgsUIntConst::eqIR(LgsModule* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return runtime->builder.CreateICmpEQ(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::neIR(LgsModule* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return runtime->builder.CreateICmpNE(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::gtIR(LgsModule* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return runtime->builder.CreateICmpSGT(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::ltIR(LgsModule* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return runtime->builder.CreateICmpSLT(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::geIR(LgsModule* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return runtime->builder.CreateICmpSGE(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::leIR(LgsModule* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return runtime->builder.CreateICmpSLE(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::andIR(LgsModule* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {}
    assert(0);
}

Value* LgsUIntConst::orIR(LgsModule* runtime, LgsExpr* other) {
    assert(0);
}

Value* LgsUIntConst::bitAndIR(LgsModule* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return runtime->builder.CreateAnd(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::bitOrIR(LgsModule* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return runtime->builder.CreateOr(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::bitXorIR(LgsModule* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return runtime->builder.CreateXor(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::lshiftIR(LgsModule* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return runtime->builder.CreateShl(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::rshiftIR(LgsModule* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return runtime->builder.CreateAShr(thisIRValue, otherIRValue);
    }
    assert(0);
}
