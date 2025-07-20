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

Value* LgsArray::getLength(LgsModule* module, LgsExpr* expr) {
    if (isStatic) return sizeExpr->getIRValue(module);
    return lenFunc.call(module, {expr});
}

Value* LgsArray::getLoopLength(LgsModule* module, LgsExpr* expr) {
    return getLength(module, expr);
}

Value* LgsArray::isEmpty(LgsModule* module, LgsExpr* expr) {
    return isEmptyFunc.call(module, {expr});
}

Value* LgsArray::isNotEmpty(LgsModule* module, LgsExpr* expr) {
    return isNotEmptyFunc.call(module, {expr});
}

StructType* LgsArray::getArrStruct(LLVMContext& context) {
    if (arrStruct) return arrStruct;
    arrStruct = getIRStructType(context, name, {i64Ty(context), i64Ty(context), i64Ty(context), ptrTy(context)});
    return arrStruct;
}

Value* LgsArrayAddFunc::call(LgsModule* module, const vector<LgsExpr*>& args) {
    vector<Value*> values;
    const auto arr = args[0];
    const auto arrSize = args.size() - 1;
    const auto baseType = arr->type->asIterable()->baseType;
    const auto arrIRType = ArrayType::get(baseType->getIRType(module->context), arrSize);
    const auto arrIRPtr = module->builder.CreateAlloca(arrIRType);
    const auto zero = module->builder.getInt32(0);
    for (int i = 1; i < args.size(); ++i) {
        const auto arg = args[i];
        const auto argValuePtr = module->builder.CreateGEP(arrIRType, arrIRPtr, {zero, module->builder.getInt32(i)});
        module->builder.CreateStore(arg->getIRValue(module), argValuePtr);
    }
    callIR(module, {arr->getIRValue(module), module->builder.getInt64(arrSize), arrIRPtr});
    return nullptr;
}

LgsArray::~LgsArray() {
    delete sizeExpr;
}
