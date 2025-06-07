#include "exprs/unary/LgsHashMap.h"

Value* LgsHashMap::createIRValue(LgsRuntime* runtime) {
    auto& builder = runtime->builder;
    const auto valueType = mapType.kvType.value;
    const auto elementSize = runtime->builder.getInt32(valueType->getSizeBytes());
    const vector<Type*> structFields = {builder.getPtrTy(), builder.getInt64Ty(), builder.getInt32Ty()};
    const auto mapStruct = getIRStructType(context, mapType.name, structFields);
    IRValue = runtime->builder.CreateAlloca(mapStruct);
    runtime->addAllocatedExpr(this);
    mapType.init.callIR(runtime, {IRValue, elementSize});
    for (const auto element : initialElements) {
        mapType.add.call(runtime, {this, element->key, element->value});
    }
    return IRValue;
}
