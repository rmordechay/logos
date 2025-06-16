#include "exprs/unary/LgsArrayExpr.h"
#include "cli/LgsCli.h"
#include "exprs/unary/LgsIterIndex.h"
#include "logos/LgsConfig.h"
#include "utils/LgsUtils.h"


string LgsArrayExpr::pName() {
    return type->pName();
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
    vector<Constant*> values;
    for (const auto element : initialElements) {
        const auto rValue = element->getIRValue(runtime);
        values.push_back(dyn_cast<Constant>(rValue));
    }
    const auto arrSize = initialElements.size();
    const auto baseIRType = arr->baseType->getIRType();
    const auto arrIRType = ArrayType::get(baseIRType, arrSize);
    const auto valueIR = ConstantArray::get(arrIRType, values);
    const auto globalVarIR = new GlobalVariable(*runtime->module, arrIRType, true, GlobalValue::PrivateLinkage, valueIR);
    const auto arrIRPtr = builder.CreateAlloca(ArrayType::get(baseIRType, arr->iterLen));
    const auto n = dataLayout.getTypeAllocSize(baseIRType).getFixedValue() * arrSize;
    builder.CreateCall(getMemcpy(runtime), {arrIRPtr, globalVarIR, builder.getInt64(n), builder.getFalse()});
    return arrIRPtr;
}

void LgsArrayExpr::free(LgsRuntime* runtime) {
    if (!type->asArray()->isStatic) {
        type->asArray()->freeFunc.call(runtime, {this});
    }
}
