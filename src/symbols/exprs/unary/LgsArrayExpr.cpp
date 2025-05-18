#include "exprs/unary/LgsArrayExpr.h"
#include "LgsConfig.h"
#include "exprs/unary/LgsIterIndex.h"

Value* LgsArrayExpr::createIRValue(CodeGenMetadata* metadata) {
    if (arrType.isStatic) return createConstArray(metadata);
    return createDynArray(metadata);
}

Value* LgsArrayExpr::createConstArray(CodeGenMetadata* metadata) const {
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

Value* LgsArrayExpr::createDynArray(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    const auto capacity = initialElements.empty() ? INITIAL_ARRAY_SIZE : initialElements.size() * 2;
    const auto capacityIR = builder.getInt32(capacity);
    IRValue = builder.CreateAlloca(ptrTy);
    const auto constantInt = builder.getInt64(sizeof(void*));
    const auto rt = arrType.new_.callIR(metadata, {capacityIR, constantInt});
    builder.CreateStore(rt, IRValue);
    for (const auto element : initialElements) {
        arrType.add.call(metadata, {this, element});
    }
    return IRValue;
}

Value* LgsArrayExpr::getLength(CodeGenMetadata* metadata) {
    if (arrType.isStatic) return arrType.dimsExprs[0]->getIRValue(metadata);
    return arrType.len.call(metadata, {this});
}