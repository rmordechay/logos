#include "exprs/unary/LgsHashMap.h"

Value* LgsHashMap::createIRValue(LgsRuntime* runtime) {
    auto& builder = runtime->builder;
    const vector<Type*> mapStructFields = {builder.getPtrTy(), builder.getInt64Ty(), builder.getInt32Ty()};
    mapType.mapStruct = getArrStruct(context, mapType.name, mapStructFields);
    const auto valueType = mapType.kvType.value;
    const auto elementSize = runtime->builder.getInt32(valueType->getSizeBytes());
    IRValue = runtime->builder.CreateAlloca(mapType.mapStruct);
    runtime->addAllocatedExpr(this);
    mapType.init.callIR(runtime, {IRValue, elementSize});
    for (const auto element : initialElements) {
        mapType.add.call(runtime, {this, element->key, element->value});
    }
    return IRValue;
}
