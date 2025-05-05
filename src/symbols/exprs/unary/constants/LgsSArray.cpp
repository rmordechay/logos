#include "exprs/unary/LgsSArray.h"

#include "types/LgsIterable.h"

Value* LgsSArray::createIRValue(CodeGenMetadata* metadata) {
    const auto irType = type->getIRType();
    const auto arrPtr = metadata->builder.CreateAlloca(irType);
    for (int i = 0; i < initialElements.size(); ++i) {
        const auto initialElement = initialElements[i];
        auto irIndex = metadata->builder.getInt32(i);
        const auto gep = metadata->builder.CreateGEP(irType, arrPtr, {i32Zero, irIndex});
        const auto rValue = initialElement->getIRValue(metadata);
        metadata->builder.CreateStore(rValue, gep);
    }
    return arrPtr;
}