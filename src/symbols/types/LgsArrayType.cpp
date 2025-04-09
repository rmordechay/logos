#include "types/LgsArrayType.h"
#include "exprs/unary/LgsArray.h"
#include <llvm/IR/DerivedTypes.h>

Type* LgsArrayType::getIRType() {
    return ptrTy;
}

size_t LgsArrayType::size() {
    return sizeof(void*);
}

const string LgsArrayType::getName() const {
    return "ArrayType";
}

LgsExpr* LgsArrayType::getZeroValue() {
    return new LgsArray(this);
}

bool LgsArrayType::equals(LgsType* other) const {
    if (const auto otherArrayType = dynamic_cast<LgsArrayType*>(other)) {
        return underlyingType->equals(otherArrayType->underlyingType);
    }
    return false;
}

LgsType* LgsArrayType::inferBinaryType(LgsType* other) {
    assert(false);
}

Value* LgsArrayType::initIRArr(CodeGenMetadata* metadata, const size_t size) const {
    auto func = metadata->module->getOrInsertFunction("ArrayType_initArr_ArrayType_Long", initArrIRFuncType);
    auto initialCapacity = metadata->builder.getInt64(size);
    const auto arrPtr = metadata->builder.CreateAlloca(arrIR);
    dyn_cast<Function>(func.getCallee())->addParamAttr(0, sret);
    return metadata->builder.CreateCall(func, {arrPtr, initialCapacity});
}

FunctionCallee LgsArrayType::getIRFuncAddElement(const CodeGenMetadata* metadata) const {
    return metadata->module->getOrInsertFunction("ArrayType_add_ArrayType_Str", addElementIRFuncType);
}

Value* LgsArrayType::getIRFuncGetElement(CodeGenMetadata* metadata, Value* arrPtr, Value* index) const {
    const auto func = metadata->module->getOrInsertFunction("ArrayType_getElement_ArrayType_Int", getElementIRFuncType);
    return metadata->builder.CreateCall(func, {arrPtr, index});
}

void LgsArrayType::free(CodeGenMetadata* metadata, bool* isFreed, Value* IRValue) const {
    if (*isFreed) return;
    const auto func = metadata->module->getOrInsertFunction("ArrayType_freeArr_ArrayType", freeArrIRFuncType);
    metadata->builder.CreateCall(func, {IRValue});
    *isFreed = true;
}
