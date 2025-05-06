#include "exprs/unary/LgsSArray.h"


Value* LgsSArray::createIRValue(CodeGenMetadata* metadata) {
    const auto IRType = type->getIRType();
    const auto arrPtr = metadata->builder.CreateAlloca(IRType);
    for (int i = 0; i < initialElements.size(); ++i) {
        const auto initialElement = initialElements[i];
        auto IRIndex = metadata->builder.getInt32(i);
        const auto gep = metadata->builder.CreateGEP(IRType, arrPtr, {i32Zero, IRIndex});
        const auto rValue = initialElement->getIRValue(metadata);
        metadata->builder.CreateStore(rValue, gep);
    }
    return arrPtr;
}