#include "exprs/unary/LgsHashMap.h"

Value* LgsHashMap::createIRValue(CodegenMetadata* metadata) {
    auto& builder = metadata->builder;
    const auto valueType = mapType.kvType.value;
    const auto elementSize = builder.getInt32(valueType->getSize());
    const auto mapStruct = getIRStructType(mapType.name, mapType.structFields);
    IRValue = builder.CreateAlloca(mapStruct);
    mapType.init.callIR(metadata, {IRValue, elementSize});
    for (const auto element : initialElements) {
        mapType.add.call(metadata, {this, element->key, element->value});
    }
    return IRValue;
}

Value* LgsHashMap::getLength(CodegenMetadata* metadata) {
    return mapType.len.call(metadata, {this});
}