#include "exprs/unary/LgsHashMap.h"

Value* LgsHashMap::createIRValue(LgsRuntime* runtime) {
    initIRMap(runtime);
    runtime->addAllocatedExpr(this);
    for (const auto element : initialElements) {
        mapType.addFunc.call(runtime, {this, element->key, element->value});
    }
    return IRValue;
}

void LgsHashMap::initIRMap(LgsRuntime* runtime) {
    const auto valueType = mapType.kvType.value;
    const auto elementSize = runtime->builder.getInt64(valueType->getSizeBytes());
    IRValue = runtime->builder.CreateAlloca(mapType.getMapStruct(runtime));
    mapType.initFunc.callIR(runtime, {IRValue, elementSize});
}
