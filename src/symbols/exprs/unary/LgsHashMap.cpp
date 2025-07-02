#include "exprs/unary/LgsHashMap.h"

#include "utils/LgsUtils.h"

Value* LgsHashMap::createIRValue(LgsModule* module) {
    initIRMap(module);
    module->addAllocatedExpr(this);
    for (const auto element : initialElements) {
        type->asMap()->addFunc.call(module, {this, element->key, element->value});
    }
    return IRValue;
}

void LgsHashMap::initIRMap(LgsModule* module) {
    const auto valueType = type->asMap()->typePair->value;
    const auto elementSize = module->builder.getInt64(valueType->getSizeBytes());
    IRValue = module->builder.CreateAlloca(type->asMap()->getMapStruct(module));
    type->asMap()->initFunc.callIR(module, {IRValue, elementSize});
}
