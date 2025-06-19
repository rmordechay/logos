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
    IRValue = builder.CreateAlloca(arrType->getArrStruct());

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
    const auto arrIRPtr = builder.CreateAlloca(arrIRType);
    if (arrSize > 0) {
        const auto type = ArrayType::get(baseIRType, arrSize);
        const auto value = createIRConstArray(runtime);
        const auto globalVarIR = createIRGlobal(runtime, type, value);
        copyMem(runtime, globalVarIR, arrIRPtr, arr->getIterBytesSize(arrSize));
    }
    return arrIRPtr;
}

Constant* LgsArrayExpr::createIRConstArray(LgsRuntime* runtime) const {
    const auto baseType = type->asArray()->baseType;
    const auto arrIRType = ArrayType::get(baseType->getIRType(), initialElements.size());
    vector<Constant*> values;
    for (const auto element : initialElements) {
        if (const auto subArray = element->asArrayExpr()) {
            auto nested = subArray->createIRConstArray(runtime);
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
