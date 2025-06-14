#include "types/LgsArray.h"

#include "builtin/LgsBuiltinFuncs.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "stmts/LgsVarDec.h"
#include "utils/LgsUtils.h"

Type* LgsArray::getIRType() {
    if (IRType) return IRType;
    if (!isStatic) return PointerType::getUnqual(context);
    const auto innerIRType = baseType->getIRType();
    IRType = ArrayType::get(innerIRType, iterLen);
    return IRType;
}

size_t LgsArray::getSizeBytes() {
    if (isStatic) {
        assert(iterLen > 0);
        return baseType->getSizeBytes() * iterLen;
    }
    return sizeof(size_t) + sizeof(size_t) + sizeof(size_t) + sizeof(void*);
}

LgsExpr* LgsArray::getZeroValue() {
    return new LgsArrayExpr(this);
}

string LgsArray::prettyName() const {
    if (!isStatic) return baseType->prettyName() + "[]";
    return baseType->prettyName() + '[' + (iterLen == 0 ? "" : to_string(iterLen)) + "]!";
}

bool LgsArray::equals(LgsType* other) {
    const auto otherArr = other->asArray();
    if (!otherArr) return false;
    if (!baseType->equals(otherArr->baseType)) return false;
    if (isStatic != otherArr->isStatic) return false;
    if (isStatic) return sizeExpr->type->equals(otherArr->sizeExpr->type);
    return true;
}

string LgsArray::getIRName() {
    return name;
}

LgsType* LgsArray::inferBinaryType(LgsType* other) {
    assert(0);
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

Value* LgsArray::isEmpty(LgsRuntime* runtime, LgsExpr* expr) {
    return isEmptyFunc.call(runtime, {expr});
}

Value* LgsArray::isNotEmpty(LgsRuntime* runtime, LgsExpr* expr) {
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

Value* LgsArrayAddFunc::call(LgsRuntime* runtime, const vector<LgsExpr*>& args) {
    const auto arrPtr = args[0]->getIRValue(runtime);
    for (int i = 1; i < args.size(); ++i) {
        const auto arg = args[i];
        const auto argValueIR = arg->getIRValue(runtime);
        const auto argValuePtr = runtime->builder.CreateAlloca(arg->type->getIRType());
        runtime->builder.CreateStore(argValueIR, argValuePtr);
        callIR(runtime, {arrPtr, argValuePtr});
    }
    return nullptr;
}

LgsArray::~LgsArray() {
    delete sizeExpr;
}
