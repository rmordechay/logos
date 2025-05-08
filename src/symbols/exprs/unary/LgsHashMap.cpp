#include "exprs/unary/LgsHashMap.h"

Value* LgsHashMap::createIRValue(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    const auto keyIRType = mapType.kvType.key->getIRType();
    const auto valueType = mapType.kvType.value;
    IRValue = builder.CreateAlloca(keyIRType);
    const auto elementSize = builder.getInt32(valueType->getSize());
    const auto rt = mapType.new_.makeCall(metadata, {elementSize});
    builder.CreateStore(rt, IRValue);
    for (const auto element : initialElements) {
        mapType.add.call(metadata, {this, element->key, element->value});
    }
    return IRValue;
}
