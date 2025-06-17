#include "exprs/unary/constants/LgsIntConst.h"
#include "exprs/unary/constants/LgsFloatConst.h"
#include "exprs/unary/constants/LgsLongConst.h"
#include "exprs/unary/constants/LgsStrConst.h"

string LgsIntConst::prettyName() {
    return to_string(value);
}

Value* LgsIntConst::createIRValue(LgsRuntime* runtime) {
    return runtime->builder.getInt32(value);
}

LgsExpr* LgsIntConst::convertExpr(LgsType* toType) {
    if (toType->asInt()) {
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

LgsExpr* LgsIntConst::clone() {
    return new LgsIntConst(value);
}

Value* LgsIntConst::andIR(LgsRuntime* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    return runtime->builder.CreateAnd(thisIRValue, otherIRValue);
}

Value* LgsIntConst::orIR(LgsRuntime* runtime, LgsExpr* other) {
    assert(0);
}

Value* LgsIntConst::bitAndIR(LgsRuntime* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    return runtime->builder.CreateAnd(thisIRValue, otherIRValue);
}

Value* LgsIntConst::bitOrIR(LgsRuntime* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    return runtime->builder.CreateOr(thisIRValue, otherIRValue);
}

Value* LgsIntConst::bitXorIR(LgsRuntime* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    return runtime->builder.CreateXor(thisIRValue, otherIRValue);
}

Value* LgsIntConst::lshiftIR(LgsRuntime* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    return runtime->builder.CreateShl(thisIRValue, otherIRValue);
}

Value* LgsIntConst::rshiftIR(LgsRuntime* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    return runtime->builder.CreateAShr(thisIRValue, otherIRValue);
}
