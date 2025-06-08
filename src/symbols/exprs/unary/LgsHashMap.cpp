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
    IRValue = runtime->builder.CreateAlloca(getMapStruct(runtime));
    mapType.init.callIR(runtime, {IRValue, elementSize});
}

StructType* LgsHashMap::getMapStruct(LgsRuntime* runtime) {
    if (mapType.mapStruct) return mapType.mapStruct;
    auto& builder = runtime->builder;
    const vector<Type*> mapStructFields = {builder.getPtrTy(), builder.getInt64Ty(), builder.getInt32Ty()};
    mapType.mapStruct = getArrStruct(context, mapType.name, mapStructFields);
    return mapType.mapStruct;
}
