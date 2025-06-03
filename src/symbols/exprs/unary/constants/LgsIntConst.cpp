#include "exprs/unary/constants/LgsIntConst.h"
#include "exprs/unary/constants/LgsFloatConst.h"
#include "exprs/unary/constants/LgsStrConst.h"

string LgsIntConst::prettyName() {
    return to_string(value);
}

Value* LgsIntConst::createIRValue(LgsRuntime* runtime) {
    return runtime->builder.getInt32(value);
}

LgsExpr* LgsIntConst::convertExpr(LgsType* other) {
    if (dynamic_cast<LgsStr*>(other)) {
        return new LgsStrConst(to_string(value));
    }
    assert(false);
}

Value* LgsIntConst::eqIR(LgsRuntime* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return runtime->builder.CreateICmpEQ(thisIRValue, otherIRValue);
    }
    assert(false);
}

Value* LgsIntConst::neIR(LgsRuntime* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return runtime->builder.CreateICmpNE(thisIRValue, otherIRValue);
    }
    assert(false);
}

Value* LgsIntConst::gtIR(LgsRuntime* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return runtime->builder.CreateICmpSGT(thisIRValue, otherIRValue);
    }
    assert(false);
}

Value* LgsIntConst::ltIR(LgsRuntime* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return runtime->builder.CreateICmpSLT(thisIRValue, otherIRValue);
    }
    assert(false);
}

Value* LgsIntConst::geIR(LgsRuntime* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return runtime->builder.CreateICmpSGE(thisIRValue, otherIRValue);
    }
    assert(false);
}

Value* LgsIntConst::leIR(LgsRuntime* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return runtime->builder.CreateICmpSLE(thisIRValue, otherIRValue);
    }
    assert(false);
}

Value* LgsIntConst::andIR(LgsRuntime* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {

    }
    assert(false);
}

Value* LgsIntConst::orIR(LgsRuntime* runtime, LgsExpr* other) {
    assert(false);
}

Value* LgsIntConst::bitAndIR(LgsRuntime* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return runtime->builder.CreateAnd(thisIRValue, otherIRValue);
    }
    assert(false);
}

Value* LgsIntConst::bitOrIR(LgsRuntime* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return runtime->builder.CreateOr(thisIRValue, otherIRValue);
    }
    assert(false);
}

Value* LgsIntConst::bitXorIR(LgsRuntime* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return runtime->builder.CreateXor(thisIRValue, otherIRValue);
    }
    assert(false);
}

Value* LgsIntConst::lshiftIR(LgsRuntime* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return runtime->builder.CreateShl(thisIRValue, otherIRValue);
    }
    assert(false);
}

LgsExpr* LgsIntConst::clone() {
    return new LgsIntConst(value);
}

Value* LgsIntConst::rshiftIR(LgsRuntime* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return runtime->builder.CreateAShr(thisIRValue, otherIRValue);
    }
    assert(false);
}
