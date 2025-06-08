#include "exprs/unary/LgsArrayExpr.h"
#include "exprs/unary/LgsIterIndex.h"
#include "logos/LgsConfig.h"


#include "utils/LgsUtils.h"

Value* LgsArrayExpr::createIRValue(LgsRuntime* runtime) {
    if (arrType.isStatic) return createConstArray(runtime);
    return createDynArray(runtime);
}

Value* LgsArrayExpr::createDynArray(LgsRuntime* runtime) {
    auto& builder = runtime->builder;
    const auto int32Ty = builder.getInt32Ty();
    const auto int64Ty = builder.getInt64Ty();
    const auto ptrTy = builder.getPtrTy();
    const auto arrStruct = getArrStruct(context, arrType.name, {int64Ty, int32Ty, int32Ty, ptrTy});
    const auto elementSize = builder.getInt64(arrType.baseType->getSizeBytes());
    IRValue = builder.CreateAlloca(arrStruct);

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
    if (!arrType.isStatic) {
        arrType.free.call(runtime, {this});
    }
}

