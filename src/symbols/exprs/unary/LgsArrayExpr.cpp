#include "exprs/unary/LgsArrayExpr.h"
#include "logos/LgsConfig.h"
#include "exprs/unary/LgsIterIndex.h"
#include "logos/LgsGlobals.h"
#include "utils/LgsUtils.h"

Value* LgsArrayExpr::createIRValue(Module* module) {
    if (arrType.isStatic) return createConstArray(module);
    return createDynArray(module);
}

Value* LgsArrayExpr::createDynArray(Module* module) {
    const auto capacity = initialElements.empty() ? INITIAL_ARRAY_CAPACITY : initialElements.size() * 2;
    const auto capacityIR = builder.getInt32(capacity);
    const auto elementSize = builder.getInt64(arrType.baseType->getSizeBytes());
    const auto arrStruct = getIRStructType(arrType.name, arrType.structFields);
    const auto currentFunc = runtime.getCurrentFunc()->getIRFunc(module);
    if (isReturnValue) {
        IRValue = currentFunc->arg_begin();
    } else {
        IRValue = builder.CreateAlloca(arrStruct);
    }
    runtime.addAllocatedExpr(this);
    arrType.init.callIR(module, {IRValue, capacityIR, elementSize});
    for (const auto element : initialElements) {
        arrType.add.call(module, {this, element});
    }
    return IRValue;
}

Value* LgsArrayExpr::createConstArray(Module* module) const {
    const auto IRType = type->getIRType();
    const auto arrPtr = builder.CreateAlloca(IRType);
    for (int i = 0; i < initialElements.size(); ++i) {
        const auto initialElement = initialElements[i];
        auto IRIndex = builder.getInt32(i);
        const auto gep = builder.CreateGEP(IRType, arrPtr, {i32Zero, IRIndex});
        const auto rValue = initialElement->getIRValue(module);
        builder.CreateStore(rValue, gep);
    }
    return arrPtr;
}

void LgsArrayExpr::free(Module* module) {
    if (arrType.isStatic) return;
    arrType.free.call(module, {this});
}

Value* LgsArrayExpr::getLength(Module* module) {
    if (arrType.isStatic) return arrType.sizeExpr->getIRValue(module);
    return arrType.len.call(module, {this});
}
