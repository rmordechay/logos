#include "exprs/unary/LgsArrayExpr.h"
#include "logos/LgsConfig.h"
#include "exprs/unary/LgsIterIndex.h"
#include "logos/LgsRuntime.h"

#include "utils/LgsUtils.h"

Value* LgsArrayExpr::createIRValue(LgsRuntime* runtime) {
    if (arrType.isStatic) return createConstArray(runtime);
    return createDynArray(runtime);
}

Value* LgsArrayExpr::createDynArray(LgsRuntime* runtime) {
    const auto capacity = initialElements.empty() ? INITIAL_ARRAY_CAPACITY : initialElements.size() * 2;
    const auto capacityIR = runtime->builder.getInt32(capacity);
    const auto elementSize = runtime->builder.getInt64(arrType.baseType->getSizeBytes());
    const auto arrStruct = getIRStructType(arrType.name, arrType.structFields);
    IRValue = runtime->builder.CreateAlloca(arrStruct);
    runtime->addAllocatedExpr(this);
    arrType.init.callIR(runtime, {IRValue, capacityIR, elementSize});
    for (const auto element : initialElements) {
        arrType.add.call(runtime, {this, element});
    }
    return IRValue;
}

Value* LgsArrayExpr::createConstArray(LgsRuntime* runtime) const {
    const auto IRType = type->getIRType();
    const auto arrPtr = runtime->builder.CreateAlloca(IRType);
    for (int i = 0; i < initialElements.size(); ++i) {
        const auto initialElement = initialElements[i];
        auto IRIndex = runtime->builder.getInt32(i);
        const auto gep = runtime->builder.CreateGEP(IRType, arrPtr, {i32Zero, IRIndex});
        const auto rValue = initialElement->getIRValue(runtime);
        runtime->builder.CreateStore(rValue, gep);
    }
    return arrPtr;
}

void LgsArrayExpr::free(LgsRuntime* runtime) {
    if (arrType.isStatic) return;
    arrType.free.call(runtime, {this});
}

Value* LgsArrayExpr::getLength(LgsRuntime* runtime) {
    if (arrType.isStatic) return arrType.sizeExpr->getIRValue(runtime);
    return arrType.len.call(runtime, {this});
}
