#include "exprs/unary/LgsArrayExpr.h"
#include "cli/LgsCli.h"
#include "exprs/unary/LgsIterIndex.h"
#include "logos/LgsConfig.h"
#include "utils/LgsUtils.h"


string LgsArrayExpr::prettyName() {
    return type->prettyName();
}

Value* LgsArrayExpr::createIRValue(LgsRuntime* runtime) {
    if (type->asArray()->isStatic) return createConstArray(runtime);
    return createDynamicArray(runtime);
}

Value* LgsArrayExpr::createDynamicArray(LgsRuntime* runtime) {
    auto& builder = runtime->builder;
    const auto arrType = type->asArray();
    const auto elementSize = builder.getInt64(arrType->baseType->getSizeBytes());
    IRValue = builder.CreateAlloca(arrType->getArrStruct(runtime));

    Value* capacityIR = nullptr;
    if (arrType->sizeExpr) {
        capacityIR = arrType->sizeExpr->getIRValue(runtime);
        capacityIR = builder.CreateZExt(capacityIR, builder.getInt64Ty());
    } else {
        const auto capacity = initialElements.empty() ? INITIAL_ARRAY_CAPACITY : initialElements.size() * 2;
        capacityIR = builder.getInt64(capacity);
    }

    arrType->initFunc.callIR(runtime, {IRValue, capacityIR, elementSize});
    for (const auto element : initialElements) {
        arrType->addFunc.call(runtime, {this, element});
    }
    runtime->addAllocatedExpr(this);
    return IRValue;
}

Value* LgsArrayExpr::createConstArray(LgsRuntime* runtime) const {
    auto& builder = runtime->builder;
    const auto arr = type->asArray();
    const auto baseType = arr->baseType;
    const auto arrSize = initialElements.size();
    const auto baseIRType = baseType->getIRType();
    const auto arrIRType = ArrayType::get(baseIRType, arr->iterLen);
    if (arrSize == 0) return runtime->builder.CreateAlloca(arrIRType);
    const auto arrIRPtr = builder.CreateAlloca(arrIRType);
    const auto initialArrIRType = ArrayType::get(baseIRType, arrSize);
    const auto valueIR = createInnerConstArray(runtime);
    const auto globalVarIR = new GlobalVariable(*runtime->module, initialArrIRType, true, GlobalValue::PrivateLinkage, valueIR);
    const auto n = dataLayout.getTypeAllocSize(baseIRType).getFixedValue() * arrSize;
    builder.CreateCall(getMemcpy(runtime), {arrIRPtr, globalVarIR, builder.getInt64(n), builder.getFalse()});
    return arrIRPtr;
}

Constant* LgsArrayExpr::createInnerConstArray(LgsRuntime* runtime) const {
    const auto arr = type->asArray();
    const auto baseType = arr->baseType;
    const auto arrSize = initialElements.size();
    const auto baseIRType = baseType->getIRType();
    const auto arrIRType = ArrayType::get(baseIRType, arrSize);
    vector<Constant*> values;
    for (const auto element : initialElements) {
        if (const auto subArray = element->asArrayExpr()) {
            auto nested = subArray->createInnerConstArray(runtime);
            values.push_back(nested);
        } else {
            const auto val = element->getIRValue(runtime);
            values.push_back(cast<Constant>(val));
        }
    }
    return ConstantArray::get(arrIRType, values);
}

void LgsArrayExpr::free(LgsRuntime* runtime) {
    if (!type->asArray()->isStatic) {
        type->asArray()->freeFunc.call(runtime, {this});
    }
}
