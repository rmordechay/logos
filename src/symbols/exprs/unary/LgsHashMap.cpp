#include "exprs/unary/LgsHashMap.h"

#include "utils/LgsUtils.h"

Value* LgsHashMap::createIRValue(LgsRuntime* runtime) {
    initIRMap(runtime);
    runtime->addAllocatedExpr(this);
    for (const auto element : initialElements) {
        type->asMap()->addFunc.call(runtime, {this, element->key, element->value});
    }
    return IRValue;
}

StructType* LgsMapEntry::getStructType() {
    auto ptrTy = PointerType::getUnqual(context);
    return getIRStructType("MapEntry", {ptrTy, ptrTy});
}

void LgsHashMap::initIRMap(LgsRuntime* runtime) {
    const auto valueType = mapType->typePair->value;
    const auto elementSize = runtime->builder.getInt64(valueType->getSizeBytes());
    IRValue = runtime->builder.CreateAlloca(type->asMap()->getMapStruct(runtime));
    type->asMap()->initFunc.callIR(runtime, {IRValue, elementSize});
}
