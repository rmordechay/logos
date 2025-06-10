#include "types/LgsArray.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "stmts/LgsVarDec.h"
#include "utils/LgsUtils.h"

Type* LgsArray::getIRType() {
    if (IRType) return IRType;
    if (!isStatic) return PointerType::getUnqual(context);
    const auto innerIRType = baseType->getIRType();
    IRType = ArrayType::get(innerIRType, constSize);
    return IRType;
}

size_t LgsArray::getSizeBytes() {
    if (isStatic) {
        assert(constSize > 0);
        return baseType->getSizeBytes() * constSize;
    }
    return sizeof(size_t) + sizeof(int) + sizeof(int) + sizeof(void*);
}

LgsExpr* LgsArray::getZeroValue() {
    return new LgsArrayExpr(this);
}

string LgsArray::prettyName() const {
    return name;
}

bool LgsArray::equals(LgsType* other) {
    const auto otherArr = other->asArray();
    if (!otherArr) return false;
    const auto isEqual = otherArr->isStatic == isStatic && baseType->equals(otherArr->baseType);
    if (!isEqual) return false;
    if (isStatic) {
        return sizeExpr->type->equals(otherArr->sizeExpr->type);
    }
    return true;
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
    return lenFunc.call(runtime, {expr});
}

Value* LgsArray::getLoopLength(LgsRuntime* runtime, LgsExpr* expr) {
    return getLength(runtime, expr);
}

Value* LgsArray::callIsEmpty(LgsRuntime* runtime, LgsExpr* expr) {
    return isEmptyFunc.call(runtime, {expr});
}

Value* LgsArray::callIsNotEmpty(LgsRuntime* runtime, LgsExpr* expr) {
    return isNotEmptyFunc.call(runtime, {expr});
}

StructType* LgsArray::getArrStruct(LgsRuntime* runtime) {
    if (arrStruct) return arrStruct;
    auto& builder = runtime->builder;
    const auto int64Ty = builder.getInt64Ty();
    const auto ptrTy = builder.getPtrTy();
    arrStruct = getIRStructType(context, name, {int64Ty, int64Ty, int64Ty, ptrTy});
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