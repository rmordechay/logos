#include "exprs/unary/LgsHashMap.h"

Value* LgsHashMap::createIRValue(LgsRuntime* runtime) {
    initIRMap(runtime);
    runtime->addAllocatedExpr(this);
    for (const auto element : initialElements) {
        mapType.add.call(runtime, {this, element->key, element->value});
    }
    return IRValue;
}

void LgsHashMap::initIRMap(LgsRuntime* runtime) {
    const auto valueType = mapType.kvType.value;
    const auto elementSize = runtime->builder.getInt32(valueType->getSizeBytes());
    IRValue = runtime->builder.CreateAlloca(mapType.getMapStruct(runtime));
    mapType.init.callIR(runtime, {IRValue, elementSize});
}
