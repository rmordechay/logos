#include "exprs/unary/LgsHashMap.h"

Value* LgsHashMap::createIRValue(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    const auto valueType = mapType.kvType.value;
    const auto elementSize = builder.getInt32(valueType->getSize());
    auto mapStruct = mapType.getIRStructType();
    IRValue = builder.CreateAlloca(mapStruct);
    mapType.init.callIR(metadata, {IRValue, elementSize});
    for (const auto element : initialElements) {
        mapType.add.call(metadata, {this, element->key, element->value});
    }
    return IRValue;
}

Value* LgsHashMap::getLength(CodeGenMetadata* metadata) {
    return mapType.len.call(metadata, {this});
}

StructType* LgsMap::getIRStructType() const {
    const auto arrStruct = StructType::getTypeByName(context, name);
    if (!arrStruct) {
        return StructType::create(context, {ptrTy, i64Ty, i32Ty}, name);
    }
    return arrStruct;
}