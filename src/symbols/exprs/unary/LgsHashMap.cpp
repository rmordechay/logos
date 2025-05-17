#include "exprs/unary/LgsHashMap.h"

Value* LgsHashMap::createIRValue(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    const auto valueType = mapType.kvType.value;
    const auto elementSize = builder.getInt32(valueType->getSize());
    IRValue = builder.CreateAlloca(ptrTy);
    const auto rv = mapType.new_.callIR(metadata, {elementSize});
    builder.CreateStore(rv, IRValue);
    for (const auto element : initialElements) {
        mapType.add.call(metadata, {this, element->key, element->value});
    }
    return IRValue;
}

Value* LgsHashMap::getLength(CodeGenMetadata* metadata) {
    return mapType.len.call(metadata, {this});
}
