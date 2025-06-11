#include "types/LgsArray.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "stmts/LgsVarDec.h"
#include "utils/LgsUtils.h"

// define i32 @main() #0 {
//   %2 = alloca %struct.HashMap, align 8
//   %3 = alloca %struct.Array, align 8
//   %4 = alloca i32, align 4
//   %5 = alloca ptr, align 8
//   %6 = alloca ptr, align 8
//   call void @Map_init(ptr noundef %2, i64 noundef 32)
//   call void @Array_init(ptr noundef %3, i64 noundef 10, i64 noundef 4)
//   store i32 7346, ptr %4, align 4
//   call void @Array_add(ptr noundef %3, ptr noundef %4)
//   store ptr @.str, ptr %5, align 8
//   %7 = load ptr, ptr %5, align 8
//   call void @Map_add(ptr noundef %2, ptr noundef %7, ptr noundef %3)
//   %8 = load ptr, ptr %5, align 8
//   %9 = call ptr @Map_get(ptr noundef %2, ptr noundef %8)
//   store ptr %9, ptr %6, align 8
//   %10 = load ptr, ptr %6, align 8
//   %11 = call ptr @Array_get(ptr noundef %10, i64 noundef 0)
//   %12 = load i32, ptr %11, align 4
//   %13 = call i32 (ptr, ...) @printf(ptr noundef @.str.1, i32 noundef %12)
//   ret i32 0
// }

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
    return baseType->prettyName() + '[' + to_string(iterLen) + "]!";
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

Value* LgsArrayAddFunc::call(LgsRuntime* runtime, const vector<LgsExpr*>& args) {
    const auto arrPtr = args[0]->getIRValue(runtime);
    const auto value = args[1];
    const auto valueIR = value->getIRValue(runtime);
    const auto valuePtr = runtime->builder.CreateAlloca(value->type->getIRType());
    runtime->builder.CreateStore(valueIR, valuePtr);
    return callIR(runtime, {arrPtr, valuePtr});
}

LgsArray::~LgsArray() {
    delete sizeExpr;
}
