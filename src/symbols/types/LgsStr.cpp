#include "data/LgsDefinitions.h"
#include "exprs/LgsNull.h"
#include "exprs/unary/LgsVariable.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "stmts/LgsVarDec.h"
#include "utils/LgsUtils.h"

size_t LgsStr::getSizeBytes() {
    if (isStatic) return iterLen + 1;
    return sizeof(void*);
}

string LgsStr::getIRName() {
    return name;
}

Type* LgsStr::getIRType() {
    if (isStatic) return ArrayType::get(baseType->getIRType(), iterLen);
    return PointerType::getUnqual(context);
}

string LgsStr::prettyName() const {
    return name;
}

LgsExpr* LgsStr::getZeroValue() {
    if (isNullable) return new LgsNull();
    return new LgsStrConst("");
}

string LgsStr::getStrFormatPart() const {
    return "%s";
}

LgsType* LgsStr::getIndexType() {
    return &LGS_INT;
}

LgsType* LgsStr::getValueType() {
    return baseType;
}

Value* LgsStr::getLength(LgsRuntime* runtime, LgsExpr* expr) {
    return lenFunc.call(runtime, {expr});
}

Value* LgsStr::getLoopLength(LgsRuntime* runtime, LgsExpr* expr) {
    const auto i32Ty = runtime->builder.getInt64Ty();
    const auto lenPtr = runtime->builder.CreateAlloca(i32Ty);
    runtime->builder.CreateStore(getLength(runtime, expr), lenPtr);
    return runtime->builder.CreateLoad(i32Ty, lenPtr);
}

Value* LgsStr::isEmpty(LgsRuntime* runtime, LgsExpr* expr) {
    return isEmptyFunc.call(runtime, {expr});
}

Value* LgsStr::isNotEmpty(LgsRuntime* runtime, LgsExpr* expr) {
    return isNotEmptyFunc.call(runtime, {expr});
}

bool LgsStr::equals(LgsType* other) {
    assert(other);
    if (other->getIRName() == LgsAny::name) return true;
    return name == other->getIRName();
}
