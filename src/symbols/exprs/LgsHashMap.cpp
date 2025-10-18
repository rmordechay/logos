#include "exprs/LgsHashMap.h"

void LgsHashMap::completeType(LgsType* toType) {
    if (!toType->asMap()) return;
    if (!type) {
        type = toType;
    }
}

std::string LgsHashMap::asText() {
    return type->pname();
}

LgsHashMap::~LgsHashMap() {
    for (const auto initialElement : pairs) {
        freeExpr(initialElement.key);
        freeExpr(initialElement.value);
    }
    pairs.clear();
}

