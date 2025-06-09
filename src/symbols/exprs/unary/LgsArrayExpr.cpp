#include "exprs/unary/LgsArrayExpr.h"
#include "exprs/unary/LgsIterIndex.h"
#include "logos/LgsConfig.h"

Value* LgsArrayExpr::createIRValue(LgsRuntime* runtime) {
    if (arrType.isStatic) return createConstArray(runtime);
    return createDynamicArray(runtime);
}

Value* LgsArrayExpr::createDynamicArray(LgsRuntime* runtime) {
    auto& builder = runtime->builder;
    const auto elementSize = builder.getInt64(arrType.baseType->getSizeBytes());
    IRValue = builder.CreateAlloca(arrType.getArrStruct(runtime));

    Value* capacityIR = nullptr;
    if (arrType.sizeExpr) {
        capacityIR = arrType.sizeExpr->getIRValue(runtime);
    } else {
        const auto capacity = initialElements.empty() ? INITIAL_ARRAY_CAPACITY : initialElements.size() * 2;
        capacityIR = builder.getInt32(capacity);
    }

    arrType.init.callIR(runtime, {IRValue, capacityIR, elementSize});
    for (const auto element : initialElements) {
        arrType.add.call(runtime, {this, element});
    }
    runtime->addAllocatedExpr(this);
    return IRValue;
}

Value* LgsArrayExpr::createConstArray(LgsRuntime* runtime) const {
    const auto IRType = type->getIRType();
    const auto arrPtr = runtime->builder.CreateAlloca(IRType);
    for (int i = 0; i < initialElements.size(); ++i) {
        const auto initialElement = initialElements[i];
        auto IRIndex = runtime->builder.getInt32(i);
        const auto gep = runtime->builder.CreateGEP(IRType, arrPtr, {runtime->builder.getInt32(0), IRIndex});
        const auto rValue = initialElement->getIRValue(runtime);
        runtime->builder.CreateStore(rValue, gep);
    }
    return arrPtr;
}


void LgsArrayExpr::free(LgsRuntime* runtime) {
    if (!arrType.isStatic) {
        arrType.free.call(runtime, {this});
    }
}
