#include "exprs/unary/LgsArrayExpr.h"
#include "exprs/unary/LgsIterIndex.h"
#include "logos/LgsConfig.h"
#include "logos/LgsRuntime.h"

#include "utils/LgsUtils.h"

Value* LgsArrayExpr::createIRValue(LgsRuntime* runtime) {
    if (arrType.isStatic) return createConstArray(runtime);
    return createDynArray(runtime);
}

Value* LgsArrayExpr::createDynArray(LgsRuntime* runtime) {
    auto& builder = runtime->builder;
    const auto capacity = initialElements.empty() ? INITIAL_ARRAY_CAPACITY : initialElements.size() * 2;
    const auto elementSize = arrType.baseType->getSizeBytes();
    const vector<Type*> structFields{builder.getInt64Ty(), builder.getInt32Ty(), builder.getInt32Ty(), builder.getPtrTy()};
    const auto arrStruct = getArrStruct(context, arrType.name, structFields);
    IRValue = builder.CreateAlloca(arrStruct);
    arrType.init.callIR(runtime, {IRValue, builder.getInt32(capacity), builder.getInt64(elementSize)});
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
    if (arrType.isStatic) return;
    arrType.free.call(runtime, {this});
}

