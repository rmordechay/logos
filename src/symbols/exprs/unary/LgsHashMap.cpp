#include "exprs/unary/LgsHashMap.h"

Value* LgsHashMap::createIRValue(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    const auto valueType = mapType.kvType.value;
    const auto elementSize = builder.getInt32(valueType->getSize());
    IRValue = builder.CreateAlloca(mapType.mapStruct);
    mapType.new_.callIR(metadata, {IRValue, elementSize});
    for (const auto element : initialElements) {
        mapType.add.call(metadata, {this, element->key, element->value});
    }
    return IRValue;
}

Value* LgsHashMap::getLength(CodeGenMetadata* metadata) {
    return mapType.len.call(metadata, {this});
}
