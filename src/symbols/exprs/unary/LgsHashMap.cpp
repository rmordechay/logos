#include "exprs/unary/LgsHashMap.h"

Value* LgsHashMap::createIRValue(LgsRuntime* runtime) {
    initIRMap(runtime);
    runtime->addAllocatedExpr(this);
    for (const auto element : initialElements) {
        type->asMap()->addFunc.call(runtime, {this, element->key, element->value});
    }
    return IRValue;
}

void LgsHashMap::initIRMap(LgsRuntime* runtime) {
    const auto valueType = map->typePair->value;
    const auto elementSize = runtime->builder.getInt64(valueType->getSizeBytes());
    IRValue = runtime->builder.CreateAlloca(type->asMap()->getMapStruct(runtime));
    type->asMap()->initFunc.callIR(runtime, {IRValue, elementSize});
}