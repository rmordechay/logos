#include "types/LgsArray.h"
#include "builtin/LgsBuiltins.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "types/primitives/LgsInt.h"
#include "utils/LgsUtils.h"

Type* LgsArray::getIRType(LLVMContext& context) {
    if (IRType) return IRType;
    if (!isStatic) return getArrStruct(context);
    const auto innerIRType = baseType->getIRType(context);
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

Value* LgsArray::getLength(LgsModule* runtime, LgsExpr* expr) {
    if (isStatic) return sizeExpr->getIRValue(runtime);
    return lenFunc.call(runtime, {expr});
}

Value* LgsArray::getLoopLength(LgsModule* runtime, LgsExpr* expr) {
    return getLength(runtime, expr);
}

Value* LgsArray::isEmpty(LgsModule* runtime, LgsExpr* expr) {
    return isEmptyFunc.call(runtime, {expr});
}

Value* LgsArray::isNotEmpty(LgsModule* runtime, LgsExpr* expr) {
    return isNotEmptyFunc.call(runtime, {expr});
}

StructType* LgsArray::getArrStruct(LLVMContext& context) {
    if (arrStruct) return arrStruct;
    arrStruct = getIRStructType(context, name, {i64Ty(context), i64Ty(context), i64Ty(context), ptrTy(context)});
    return arrStruct;
}

Value* LgsArrayAddFunc::call(LgsModule* runtime, const vector<LgsExpr*>& args) {
    vector<Value*> values;
    const auto arr = args[0];
    const auto arrSize = args.size() - 1;
    const auto baseType = arr->type->asIterable()->baseType;
    const auto arrIRType = ArrayType::get(baseType->getIRType(runtime->context), arrSize);
    const auto arrIRPtr = runtime->builder.CreateAlloca(arrIRType);
    const auto zero = runtime->builder.getInt32(0);
    for (int i = 1; i < args.size(); ++i) {
        const auto arg = args[i];
        const auto argValuePtr = runtime->builder.CreateGEP(arrIRType, arrIRPtr, {zero, runtime->builder.getInt32(i)});
        runtime->builder.CreateStore(arg->getIRValue(runtime), argValuePtr);
    }
    callIR(runtime, {arr->getIRValue(runtime), runtime->builder.getInt64(arrSize), arrIRPtr});
    return nullptr;
}

Type* LgsArrayAddFunc::getIRFuncType(LLVMContext& context) {
    const auto& params = funcType->params;
    const vector<Type*> IRParamsTypes = {
        ptrTy(context),
        i64Ty(context),
        params[1].type->getIRType(context)
    };
    return FunctionType::get(funcType->rt->getIRType(context), IRParamsTypes, false);
}

LgsArray::~LgsArray() {
    delete sizeExpr;
}
