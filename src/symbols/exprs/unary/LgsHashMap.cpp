#include "exprs/unary/LgsHashMap.h"

#include "utils/LgsUtils.h"

Value* LgsHashMap::createIRValue(LgsModule* runtime) {
    initIRMap(runtime);
    runtime->addAllocatedExpr(this);
    for (const auto element : initialElements) {
        type->asMap()->addFunc.call(runtime, {this, element->key, element->value});
    }
    return IRValue;
}

void LgsHashMap::initIRMap(LgsModule* runtime) {
    const auto valueType = type->asMap()->typePair->value;
    const auto elementSize = runtime->builder.getInt64(valueType->getSizeBytes());
    IRValue = runtime->builder.CreateAlloca(type->asMap()->getMapStruct(runtime));
    type->asMap()->initFunc.callIR(runtime, {IRValue, elementSize});
}
