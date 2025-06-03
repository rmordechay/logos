#include "exprs/unary/LgsHashMap.h"

Value* LgsHashMap::createIRValue(LgsRuntime* runtime) {

    const auto valueType = mapType.kvType.value;
    const auto elementSize = builder.getInt32(valueType->getSizeBytes());
    const auto mapStruct = getIRStructType(mapType.name, mapType.structFields);
    IRValue = builder.CreateAlloca(mapStruct);
    mapType.init.callIR(runtime, {IRValue, elementSize});
    for (const auto element : initialElements) {
        mapType.add.call(runtime, {this, element->key, element->value});
    }
    return IRValue;
}

Value* LgsHashMap::getLength(LgsRuntime* runtime) {
    return mapType.len.call(runtime, {this});
}