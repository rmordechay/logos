#include "exprs/unary/LgsArray.h"
#include "types/LgsArrayType.h"

Value* LgsArray::createIRValue(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    const auto arrayType = getArrayType();
    const auto IRArr = arrayType->initIRArr(metadata, length());
    const auto addElementFunc = arrayType->getIRFuncAddElement(metadata);
    for (const auto & element : initialElements) {
        builder.CreateCall(addElementFunc, {IRArr, element->getIRValue(metadata)});
    }
    return IRArr;
}

size_t LgsArray::length() const {
    return initialElements.size();
}

LgsArrayType* LgsArray::getArrayType() const {
    return dynamic_cast<LgsArrayType*>(type);
}

bool LgsArray::isIterable() {
    return true;
}

void LgsArray::free(CodeGenMetadata* metadata) {
    getArrayType()->free(metadata, &isFreed, IRValue);
}
