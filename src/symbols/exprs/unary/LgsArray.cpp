#include "exprs/unary/LgsArray.h"
#include "types/LgsVoid.h"

Value* LgsArray::createIRValue(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    const auto initArrFunc = getIRFuncInitArr(metadata);
    const auto addElementFunc = getIRFuncAddElement(metadata);
    const auto callInst = builder.CreateCall(initArrFunc);
    for (const auto & element : initialElements) {
        builder.CreateCall(addElementFunc, {callInst, element->getIRValue(metadata)});
    }
    return callInst;
}

size_t LgsArray::size() {
    return initialElements.size();
}

FunctionCallee LgsArray::getIRFuncInitArr(const CodeGenMetadata* metadata) const {
    return metadata->currentModule->getOrInsertFunction("ArrayType_initArr", initArrIRFuncType);
}

void LgsArray::free(CodeGenMetadata* metadata) {
    const auto func = metadata->currentModule->getOrInsertFunction("ArrayType_freeArr_ArrayType", freeArrIRFuncType);
    metadata->builder.CreateCall(func);
}

FunctionCallee LgsArray::getIRFuncAddElement(const CodeGenMetadata* metadata) const {
    return metadata->currentModule->getOrInsertFunction("ArrayType_add_ArrayType_Int", addElementIRFuncType);
}

