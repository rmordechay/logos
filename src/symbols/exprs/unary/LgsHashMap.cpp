#include "exprs/unary/LgsHashMap.h"

#include "utils/LgsUtils.h"

Value* LgsHashMap::createIRValue(LgsModule* module) {
    const auto mapType = type->asMap();
    const auto valueType = mapType->typePair->value;
    const auto elementSize = i64(module, valueType->getSizeBytes());
    IRValue = module->builder.CreateAlloca(mapType->getMapStruct(module));
    mapType->initFunc.callIR(module, {IRValue, elementSize});

    module->stack.addAllocatedExpr(this);
    for (const auto element : initialElements) {
        mapType->addFunc.call(module, {this, element->key, element->value});
    }
    return IRValue;
}
