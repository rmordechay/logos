#include "types/LgsArray.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "stmts/LgsVarDec.h"

size_t LgsArray::getSizeBytes() {
    if (isStatic) {
        return baseType->getSizeBytes() * getExprConstNumber(sizeExpr);
    }
    return sizeof(void*);
}

LgsExpr* LgsArray::getZeroValue() {
    const auto arrExpr = new LgsArrayExpr(baseType);
    arrExpr->arrType.isStatic = isStatic;
    arrExpr->arrType.sizeExpr = sizeExpr;
    return arrExpr;
}

string LgsArray::prettyName() const {
    return name;
}

bool LgsArray::equals(LgsType* other) {
    const auto otherArr = other->asArray();
    if (!otherArr) return false;
    return baseType->equals(otherArr->baseType);
}

string LgsArray::getIRName() {
    return name;
}

LgsType* LgsArray::inferBinaryType(LgsType* other) {
    assert(false);
}

void LgsArray::unpackTypes(const vector<LgsVarDec*>& varDecs) {
    varDecs[0]->type = baseType;
}

Value* LgsArray::getLength(LgsRuntime* runtime, LgsExpr* expr) {
    if (isStatic) return sizeExpr->getIRValue(runtime);
    return len.call(runtime, {expr});
}

Value* LgsArray::getLoopLength(LgsRuntime* runtime, LgsExpr* expr) {
    return getLength(runtime, expr);
}

Value* LgsArray::callIsEmpty(LgsRuntime* runtime, LgsExpr* expr) {
    return isEmpty.call(runtime, {expr});
}

Value* LgsArray::callIsNotEmpty(LgsRuntime* runtime, LgsExpr* expr) {
    return isNotEmpty.call(runtime, {expr});
}

StructType* LgsArray::getArrStruct(LgsRuntime* runtime) {
    if (arrStruct) return arrStruct;
    auto& builder = runtime->builder;
    const auto int32Ty = builder.getInt32Ty();
    const auto int64Ty = builder.getInt64Ty();
    const auto ptrTy = builder.getPtrTy();
    arrStruct = getIRStructType(context, name, {int64Ty, int32Ty, int32Ty, ptrTy});
    return arrStruct;
}

LgsType* LgsArray::clone() {
    const auto arr = new LgsArray(baseType);
    if (sizeExpr) {
        arr->isStatic = isStatic;
        arr->sizeExpr = sizeExpr;
    }
    return arr;
}

LgsArray::~LgsArray() {
    delete sizeExpr;
}
