#include "exprs/LgsHashMap.h"

#include "LgsUtils.h"

#include <iostream>

void LgsHashMap::castImplicitly(LgsType* toType) {
    if (!toType->asMap()) return;
    if (!type) {
        setType(toType);
    }
}

Value* LgsHashMap::castIR(LgsCgModule& cg, LgsType* toType) {
    assert(0);
}

bool LgsHashMap::equals(LgsExpr* other) {
    assert(0);
}

std::string LgsHashMap::asText() {
    return type->pname();
}

LgsHashMap::~LgsHashMap() {
    for (const auto [key, value] : elements) {
        freeExpr(key);
        freeExpr(value);
    }
    elements.clear();
}

