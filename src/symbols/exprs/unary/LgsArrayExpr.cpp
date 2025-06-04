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
    auto& builder = runtime->builder;
    const auto capacityIR = builder.getInt32(capacity);
    const auto elementSize = builder.getInt64(arrType.baseType->getSizeBytes());
    const vector<Type*> structFields{builder.getInt64Ty(), builder.getInt32Ty(), builder.getInt32Ty(), builder.getPtrTy()};
    const auto arrStruct = getIRStructType(context, arrType.name, structFields);
    IRValue = builder.CreateAlloca(arrStruct);
    runtime->addAllocatedExpr(this);
    arrType.init.callIR(runtime, {IRValue, capacityIR, elementSize});
    for (const auto element : initialElements) {
        arrType.add.call(runtime, {this, element});
    }
    return IRValue;
}

Value* LgsArrayExpr::createConstArray(LgsRuntime* runtime) const {
    const auto IRType = type->getIRType(runtime);
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
    if (arrType.isStatic) return;
    arrType.free.call(runtime, {this});
}

Value* LgsArrayExpr::getLength(LgsRuntime* runtime) {
    if (arrType.isStatic) return arrType.sizeExpr->getIRValue(runtime);
    return arrType.len.call(runtime, {this});
}
