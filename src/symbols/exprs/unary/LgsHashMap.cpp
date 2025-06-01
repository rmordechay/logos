#include "exprs/unary/LgsHashMap.h"

Value* LgsHashMap::createIRValue(Module* module) {

    const auto valueType = mapType.kvType.value;
    const auto elementSize = builder.getInt32(valueType->getSize());
    const auto mapStruct = getIRStructType(mapType.name, mapType.structFields);
    IRValue = builder.CreateAlloca(mapStruct);
    mapType.init.callIR(module, {IRValue, elementSize});
    for (const auto element : initialElements) {
        mapType.add.call(module, {this, element->key, element->value});
    }
    return IRValue;
}

Value* LgsHashMap::getLength(Module* module) {
    return mapType.len.call(module, {this});
}