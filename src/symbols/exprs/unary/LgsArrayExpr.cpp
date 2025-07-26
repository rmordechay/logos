#include "exprs/unary/LgsArrayExpr.h"
#include "cli/LgsCli.h"
#include "exprs/unary/LgsIterIndex.h"
#include "logos/LgsConfig.h"
#include "utils/LgsUtils.h"

string LgsArrayExpr::prettyName() {
    return type->prettyName();
}

Value* LgsArrayExpr::createIRValue(LgsModule* module) {
    if (type->asSArray()) return createConstArray(module);
    if (type->asDArray()) return createDynamicArray(module);
    assert(0);
}

Value* LgsArrayExpr::createDynamicArray(LgsModule* module) {
    auto& builder = module->builder;
    const auto arrType = type->asDArray();
    const auto elementSize = i64(module, arrType->baseType->getSizeBytes());
    IRValue = builder.CreateAlloca(arrType->getArrStruct(module));

    Value* capacityIR = nullptr;
    if (arrType->sizeExpr) {
        capacityIR = arrType->sizeExpr->getIRValue(module);
        capacityIR = builder.CreateZExt(capacityIR, i64Ty(module));
    } else {
        const auto capacity = initialElements.empty() ? INITIAL_ARRAY_CAPACITY : initialElements.size() * 2;
        capacityIR = i64(module, capacity);
    }

    arrType->initFunc.callIR(module, {IRValue, capacityIR, elementSize});
    for (const auto element : initialElements) {
        arrType->addFunc.call(module, {this, element});
    }
    return IRValue;
}

Value* LgsArrayExpr::createConstArray(LgsModule* module) const {
    auto& builder = module->builder;
    const auto arr = type->asSArray();
    const auto baseType = arr->baseType;
    const auto baseIRType = baseType->getIRType(module);
    const auto arrIRType = ArrayType::get(baseIRType, arr->initialLength);
    const auto arrIRPtr = builder.CreateAlloca(arrIRType);
    if (initialElements.empty()) return arrIRPtr;
    for (int i = 0; i < initialElements.size(); ++i) {
        const auto gep = builder.CreateGEP(arrIRType, arrIRPtr, {i32(module, 0), i32(module, i)});
        const auto val = initialElements[i]->getIRValue(module);
        builder.CreateStore(val, gep);
    }
    return arrIRPtr;
}

void LgsArrayExpr::free(LgsModule* module) {
    if (!type->asDArray()) return;
    type->asDArray()->freeFunc.call(module, {this});
}
