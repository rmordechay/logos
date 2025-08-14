#include "exprs/unary/LgsHashMap.h"

std::string LgsHashMap::prettyName() {
    return type->prettyName();
}

Value* LgsHashMap::createIRValue(LgsCodeGen* codeGen) {
    const auto mapType = type->asMap();
    const auto valueType = mapType->typePair->value;
    const auto elementSize = codeGen->i64(valueType->getSizeBytes());
    IRValue = codeGen->builder.CreateAlloca(mapType->getMapStruct(codeGen));
    mapType->initFunc.callIR(codeGen, {IRValue, elementSize});
    for (const auto element : initialElements) {
        mapType->addFunc.call(codeGen, {this, element->key, element->value});
    }
    return IRValue;
}
