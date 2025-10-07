#include "exprs/LgsHashMap.h"

void LgsHashMap::completeType(LgsType* toType) {
    if (!toType->asMap()) return;
    if (!type) {
        type = toType;
    }
}

std::string LgsHashMap::getName() {
    return type->pname();
}

void LgsHashMap::parseAsJSON(std::stringstream& json) {
    assert(0);
}

LgsHashMap::~LgsHashMap() {
    for (const auto initialElement : pairs) {
        freeExpr(initialElement.key);
        freeExpr(initialElement.value);
    }
    pairs.clear();
}

