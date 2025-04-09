#include "exprs/unary/LgsArray.h"
#include "types/LgsArrayType.h"

Value* LgsArray::createIRValue(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    const auto arrayType = asArrayType();
    const auto IRArr = arrayType->initIRArr(metadata, length());
    const auto addElementFunc = arrayType->getIRFuncAddElement(metadata);
    for (const auto & element : initialElements) {
        builder.CreateCall(addElementFunc, {IRArr, element->getIRValue(metadata)});
    }
    return IRArr;
}

size_t LgsArray::length() {
    return initialElements.size();
}

Value* LgsArray::sizeIR(CodeGenMetadata* metadata) {
    return nullptr;
}

LgsArrayType* LgsArray::asArrayType() const {
    return dynamic_cast<LgsArrayType*>(type);
}

void LgsArray::free(CodeGenMetadata* metadata) {
    asArrayType()->free(metadata, &isFreed, IRValue);
}