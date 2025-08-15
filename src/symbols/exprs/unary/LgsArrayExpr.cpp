#include "exprs/unary/LgsArrayExpr.h"
#include "cli/LgsCli.h"
#include "exprs/unary/LgsIterIndex.h"
#include "configs/LgsConfig.h"

std::string LgsArrayExpr::prettyName() {
    return type->prettyName();
}

void LgsArrayExpr::createIRValue(LgsCodeGen* codeGen) {
    if (type->asSArray()) IRValue = createConstArray(codeGen);
    else if (type->asDArray()) IRValue = createDynamicArray(codeGen);
    assert(0);
}

Value* LgsArrayExpr::createDynamicArray(LgsCodeGen* codeGen) {
    auto& builder = codeGen->builder;
    const auto arrType = type->asDArray();
    const auto elementSize = codeGen->i64(arrType->baseType->getSizeBytes());
    const auto arrSize = codeGen->typeSize(arrType->getArrStruct(codeGen));
    IRValue = codeGen->callMalloc(arrSize.getFixedValue());

    Value* capacityIR = nullptr;
    if (arrType->sizeExpr) {
        capacityIR = arrType->sizeExpr->getIRValue(codeGen);
        capacityIR = builder.CreateZExt(capacityIR, codeGen->i64Ty());
    } else {
        const auto capacity = initialElements.empty() ? INITIAL_ARRAY_CAPACITY : initialElements.size() * 2;
        capacityIR = codeGen->isize(capacity);
    }

    arrType->initFunc.callIR(codeGen, {IRValue, capacityIR, elementSize});
    for (const auto element : initialElements) {
        arrType->addFunc.call(codeGen, {this, element});
    }
    return IRValue;
}

Value* LgsArrayExpr::createConstArray(LgsCodeGen* codeGen) const {
    auto& builder = codeGen->builder;
    const auto arr = type->asSArray();
    const auto baseType = arr->baseType;
    const auto baseIRType = baseType->getIRType(codeGen);
    const auto arrIRType = ArrayType::get(baseIRType, arr->initialLength);
    const auto arrIRPtr = builder.CreateAlloca(arrIRType);
    if (initialElements.empty()) return arrIRPtr;
    for (int i = 0; i < initialElements.size(); ++i) {
        const auto gep = builder.CreateGEP(arrIRType, arrIRPtr, {codeGen->i32Zero(), codeGen->i32(i)});
        const auto val = initialElements[i]->getIRValue(codeGen);
        builder.CreateStore(val, gep);
    }
    return arrIRPtr;
}