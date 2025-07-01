#include "exprs/LgsNullValue.h"
#include "exprs/unary/LgsVariable.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "stmts/LgsVarDec.h"

size_t LgsStr::getSizeBytes() {
    if (isStatic) return iterLen + 1;
    return sizeof(void*);
}

string LgsStr::getIRName() {
    return name;
}

Type* LgsStr::getIRType(LLVMContext& context) {
    if (isStatic) return ArrayType::get(baseType->getIRType(context), iterLen);
    return ptrTy(context);
}

string LgsStr::prettyName() const {
    return name;
}

LgsExpr* LgsStr::getZeroValue() {
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

Value* LgsStr::getLength(LgsModule* runtime, LgsExpr* expr) {
    return lenFunc.call(runtime, {expr});
}

Value* LgsStr::getLoopLength(LgsModule* runtime, LgsExpr* expr) {
    const auto i32Ty = runtime->builder.getInt64Ty();
    const auto lenPtr = runtime->builder.CreateAlloca(i32Ty);
    runtime->builder.CreateStore(getLength(runtime, expr), lenPtr);
    return runtime->builder.CreateLoad(i32Ty, lenPtr);
}

Value* LgsStr::isEmpty(LgsModule* runtime, LgsExpr* expr) {
    return isEmptyFunc.call(runtime, {expr});
}

Value* LgsStr::isNotEmpty(LgsModule* runtime, LgsExpr* expr) {
    return isNotEmptyFunc.call(runtime, {expr});
}

bool LgsStr::equals(LgsType* other) {
    assert(other);
    if (other->getIRName() == LgsAny::name) return true;
    return name == other->getIRName();
}
