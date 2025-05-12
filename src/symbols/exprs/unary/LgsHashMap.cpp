#include "exprs/unary/LgsHashMap.h"

Value* LgsHashMap::createIRValue(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    const auto valueType = mapType.kvType.value;
    const auto elementSize = builder.getInt32(valueType->getSize());
    IRValue = mapType.new_.callIR(metadata, {elementSize});
    for (const auto element : initialElements) {
        mapType.add.call(metadata, {this, element->key, element->value});
    }
    return IRValue;
}
