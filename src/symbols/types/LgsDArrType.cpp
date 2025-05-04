#include "types/LgsDArrType.h"
#include "exprs/unary/LgsDArray.h"
#include <llvm/IR/DerivedTypes.h>

FunctionType* const initArrIRFuncType = FunctionType::get(voidTy, {ptrTy, i64Ty, i64Ty}, false);
FunctionType* const freeArrIRFuncType = FunctionType::get(voidTy, {ptrTy}, false);
FunctionType* const addElementIRFuncType = FunctionType::get(voidTy, {ptrTy, ptrTy}, false);
FunctionType* const getElementIRFuncType = FunctionType::get(ptrTy, {ptrTy, i32Ty}, false);
StructType* const arrIR = StructType::create(context, {i64Ty, i64Ty, ptrTy});
Attribute const sret = Attribute::getWithStructRetType(context, arrIR);

Type* LgsDArrType::getIRType() {
    return ptrTy;
}

const string LgsDArrType::getName() const {
    return name;
}

LgsExpr* LgsDArrType::getZeroValue() {
    return new LgsDArray(underlyingType);
}

bool LgsDArrType::equals(LgsType* other) const {
    return false;
}

LgsType* LgsDArrType::inferBinaryType(LgsType* other) {
    assert(false);
}

Value* LgsDArrType::getIRFuncGetElement(CodeGenMetadata* metadata, Value* arrPtr, Value* index) const {
    const auto func = metadata->module->getOrInsertFunction("ArrayType_getElement_ArrayType_Int", getElementIRFuncType);
    return metadata->builder.CreateCall(func, {arrPtr, index});
}
