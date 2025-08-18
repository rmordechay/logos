#include "exprs/unary/LgsHashMap.h"

void LgsHashMap::createIRValue(LgsCodeGen* codeGen) {
    const auto mapType = type->asMap();
    const auto valueType = mapType->typePair->value;
    const auto elementSize = codeGen->isize(valueType->getSizeBytes());
    IRValue = codeGen->builder.CreateAlloca(mapType->getMapStruct(codeGen));
    mapType->initFunc->callIR(codeGen, {IRValue, elementSize});
    for (const auto element : initialElements) {
        mapType->addFunc->call(codeGen, {this, element->key, element->value});
    }
}

std::string LgsHashMap::pname() {
    return type->pname();
}

LgsHashMap::~LgsHashMap() {
    for (const auto initialElement : initialElements) {
        delete initialElement;
    }
    initialElements.clear();
}

LgsMapEntry::~LgsMapEntry() {
    if (key) {
        delete key;
        key = nullptr;
    }
    if (value) {
        delete value;
        value = nullptr;
    }
}