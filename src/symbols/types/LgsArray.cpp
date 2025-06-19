#include "types/LgsArray.h"
#include "builtin/LgsBuiltins.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "types/primitives/LgsInt.h"
#include "utils/LgsUtils.h"

Type* LgsArray::getIRType() {
    if (IRType) return IRType;
    if (!isStatic) return getArrStruct();
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

LgsType* LgsArray::getIndexType() {
    return &LGS_INT;
}

LgsType* LgsArray::getValueType() {
    return baseType;
}

string LgsArray::getStrFormatPart() const {
    return "%p";
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

StructType* LgsArray::getArrStruct() {
    if (arrStruct) return arrStruct;
    const auto int64Ty = Type::getInt32Ty(context);
    const auto ptrTy = PointerType::getUnqual(context);
    arrStruct = getIRStructType(name, {int64Ty, int64Ty, int64Ty, ptrTy});
    return arrStruct;
}

Value* LgsArrayAddFunc::call(LgsRuntime* runtime, const vector<LgsExpr*>& args) {
    vector<Value*> values;
    const auto arr = args[0];
    const auto arrSize = args.size() - 1;
    const auto baseType = arr->type->asIterable()->baseType;
    const auto arrIRType = ArrayType::get(baseType->getIRType(), arrSize);
    const auto arrIRPtr = runtime->builder.CreateAlloca(arrIRType);
    const auto zero = runtime->builder.getInt32(0);
    for (int i = 1; i < arrSize; ++i) {
        const auto arg = args[i];
        const auto argValuePtr = runtime->builder.CreateGEP(arrIRType, arrIRPtr, {zero, runtime->builder.getInt32(i)});
        runtime->builder.CreateStore(arg->getIRValue(runtime), argValuePtr);
    }
    callIR(runtime, {arr->getIRValue(runtime), runtime->builder.getInt64(arrSize), arrIRPtr});
    return nullptr;
}

Type* LgsArrayAddFunc::getIRFuncType() {
    const auto& params = funcType->params;
    const vector<Type*> IRParamsTypes = {
        PointerType::getUnqual(context),
        Type::getInt64Ty(context),
        params[1].type->getIRType()
    };
    return FunctionType::get(funcType->rt->getIRType(), IRParamsTypes, false);
}

LgsArray::~LgsArray() {
    delete sizeExpr;
}
