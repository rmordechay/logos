#include "exprs/unary/constants/LgsIntConst.h"
#include "exprs/unary/constants/LgsFloatConst.h"
#include "exprs/unary/constants/LgsLongConst.h"
#include "exprs/unary/constants/LgsStrConst.h"

// define i32 @main() {
//     entry:
//       %0 = alloca %Map, align 8
//       %1 = alloca %Array, align 8
//       call void @Map_init(ptr %0, i64 24)
//       call void @Array_init(ptr %1, i64 1, i64 4)
//       %2 = alloca i32, align 4
//       store i32 7346, ptr %2, align 4
//       call void @Array_add(ptr %1, ptr %2)
//       %3 = alloca ptr, align 8
//       store ptr @1, ptr %3, align 8
//       %4 = load ptr, ptr %3, align 8
//       call void @Map_add(ptr %0, ptr %4, ptr %1)
//       %5 = alloca ptr, align 8
//       store ptr @1, ptr %5, align 8
//       %6 = load ptr, ptr %5, align 8
//       %7 = call ptr @Map_get(ptr %0, ptr %6)
//       %8 = alloca ptr, align 8
//       store ptr %7, ptr %8, align 8
//       %9 = load ptr, ptr %8, align 8
//       %10 = call ptr @Array_get(ptr %9, i64 0)
//       %11 = load i32, ptr %10, align 4
//       %12 = call i32 (ptr, ...) @printf(ptr @2, i32 %11)
//       ret i32 0
//     }
string LgsIntConst::prettyName() {
    return to_string(value);
}

Value* LgsIntConst::createIRValue(LgsRuntime* runtime) {
    return runtime->builder.getInt32(value);
}

LgsExpr* LgsIntConst::convertExpr(LgsType* toType) {
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

Value* LgsIntConst::eqIR(LgsRuntime* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return runtime->builder.CreateICmpEQ(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsIntConst::neIR(LgsRuntime* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return runtime->builder.CreateICmpNE(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsIntConst::gtIR(LgsRuntime* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return runtime->builder.CreateICmpSGT(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsIntConst::ltIR(LgsRuntime* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return runtime->builder.CreateICmpSLT(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsIntConst::geIR(LgsRuntime* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return runtime->builder.CreateICmpSGE(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsIntConst::leIR(LgsRuntime* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return runtime->builder.CreateICmpSLE(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsIntConst::andIR(LgsRuntime* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {

    }
    assert(0);
}

Value* LgsIntConst::orIR(LgsRuntime* runtime, LgsExpr* other) {
    assert(0);
}

Value* LgsIntConst::bitAndIR(LgsRuntime* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return runtime->builder.CreateAnd(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsIntConst::bitOrIR(LgsRuntime* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return runtime->builder.CreateOr(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsIntConst::bitXorIR(LgsRuntime* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return runtime->builder.CreateXor(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsIntConst::lshiftIR(LgsRuntime* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return runtime->builder.CreateShl(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsIntConst::rshiftIR(LgsRuntime* runtime, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(runtime);
    const auto thisIRValue = getIRValue(runtime);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return runtime->builder.CreateAShr(thisIRValue, otherIRValue);
    }
    assert(0);
}
