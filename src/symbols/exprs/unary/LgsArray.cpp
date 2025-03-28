#include "exprs/unary/LgsArray.h"
#include "types/LgsVoid.h"

Value* LgsArray::createIRValue(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    const auto IRArr = initIRArr(metadata);
    const auto addElementFunc = getIRFuncAddElement(metadata);
    for (const auto & element : initialElements) {
        builder.CreateCall(addElementFunc, {IRArr, element->getIRValue(metadata)});
    }
    return IRArr;
}

size_t LgsArray::size() {
    return initialElements.size();
}

Value* LgsArray::initIRArr(CodeGenMetadata* metadata) const {
    const auto func = metadata->currentModule->getOrInsertFunction("ArrayType_initArr", initArrIRFuncType);
    return metadata->builder.CreateCall(func);
}

FunctionCallee LgsArray::getIRFuncAddElement(const CodeGenMetadata* metadata) const {
    return metadata->currentModule->getOrInsertFunction("ArrayType_add_ArrayType_Int", addElementIRFuncType);
}

Value* LgsArray::getIRFuncGetElement(CodeGenMetadata* metadata, Value* index) const {
    const auto func = metadata->currentModule->getOrInsertFunction("ArrayType_getElement_ArrayType_Int", getElementIRFuncType);
    return metadata->builder.CreateCall(func, {IRValue, index});
}

void LgsArray::free(CodeGenMetadata* metadata) {
    if (isFreed) return;
    const auto func = metadata->currentModule->getOrInsertFunction("ArrayType_freeArr_ArrayType", freeArrIRFuncType);
    metadata->builder.CreateCall(func);
    isFreed = true;
}
